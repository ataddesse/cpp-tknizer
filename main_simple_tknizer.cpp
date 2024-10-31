#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "json.hpp"
#include <unicode/uchar.h>
#include <cstdlib>
#include "tokenizer_config.hpp"

using namespace std;
using json = nlohmann::json;


std::string tknzierJson = TOKENIZER_CONFIG;

template <std::ctype_base::mask mask>
class IsNot
{
  std::locale myLocale;
  std::ctype<char> const *myCType;

public:
  IsNot(std::locale const &l = std::locale())
      : myLocale(l), myCType(&std::use_facet<std::ctype<char>>(l))
  {
  }
  bool operator()(char ch) const
  {
    return !myCType->is(mask, ch);
  }
};

typedef IsNot<std::ctype_base::space> IsNotSpace;

std::string trim(std::string const &original)
{
  std::string::const_iterator right = std::find_if(original.rbegin(), original.rend(), IsNotSpace()).base();
  std::string::const_iterator left = std::find_if(original.begin(), right, IsNotSpace());
  return std::string(left, right);
}

std::vector<std::wstring> split(const std::wstring &input)
{
  std::wstringstream stream(input);
  std::vector<std::wstring> words;
  std::wstring word;
  while (stream >> word)
  {
    words.push_back(word);
  }
  return words;
}

// bool isPunctuation(UChar32 charCode) {
//     UCharCategory category = static_cast<UCharCategory>(u_charType(charCode));

//     switch (category) {
//         case U_DASH_PUNCTUATION:
//         case U_START_PUNCTUATION:
//         case U_END_PUNCTUATION:
//         case U_CONNECTOR_PUNCTUATION:
//         case U_OTHER_PUNCTUATION:
//         case U_INITIAL_PUNCTUATION:
//         case U_FINAL_PUNCTUATION:
//             return true;
//         default:
//             return false;
//     }
// }

bool _is_punctuation(UChar32 c)
{
  if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126))
  {
    return true;
  }
  // if (isPunctuation(c)) {
  //     return true;
  // }
  return false;
}

vector<wstring> run_split_on_func(const wstring &text)
{
  size_t i = 0;
  bool start_new_word = true;
  vector<vector<wchar_t>> output;

  while (i < text.length())
  {
    wchar_t c = text[i];
    if (_is_punctuation(static_cast<UChar32>(c)))
    {
      vector<wchar_t> s;
      s.push_back(c);
      output.push_back(s);
      start_new_word = true;
    }
    else
    {
      if (start_new_word)
      {
        vector<wchar_t> empty_str;
        output.push_back(empty_str);
      }
      start_new_word = false;
      output.back().push_back(c);
    }
    i++;
  }

  vector<wstring> out_str;
  for (size_t i = 0; i < output.size(); i++)
  {
    wstring s(output[i].begin(), output[i].end());
    out_str.push_back(s);
  }
  return out_str;
}

std::string wstring_to_utf8(const std::wstring &wstr)
{
  // Convert wstring to string using mbstowcs
  std::string result(wstr.size(), '\0');
  std::wcstombs(&result[0], wstr.c_str(), wstr.size());
  return result;
}

std::wstring utf8_to_wstring(const std::string &str)
{
  // Convert string to wstring using wcstombs
  std::wstring result(str.size(), L'\0');
  std::mbstowcs(&result[0], str.c_str(), str.size());
  return result;
}

class WordPieceTokenizer
{
private:
  json jsonObj;
  json vocab;
  size_t max_input_chars_per_word;
  wstring unk_token;

public:
  WordPieceTokenizer(const string &json_string)
  {
    jsonObj = json::parse(json_string); // Parse the JSON string directly
    vocab = jsonObj["model"]["vocab"];
    max_input_chars_per_word = jsonObj["model"]["max_input_chars_per_word"];
    unk_token = utf8_to_wstring(jsonObj["model"]["unk_token"]);
  }

  int get_word_index(const wstring &word)
  {
    string w_word = wstring_to_utf8(word);
    if (vocab.find(w_word) != vocab.end())
    {
      return vocab[w_word];
    }
    else
    {
      return -1;
    }
  }

  vector<int64_t> tokenize_full(const wstring &input_text)
  {
    vector<wstring> tokens = split(input_text);
    vector<wstring> basic_tokenized;
    for (size_t i = 0; i < tokens.size(); i++)
    {
      auto splitted_by_punc = run_split_on_func(tokens[i]);
      basic_tokenized.insert(basic_tokenized.end(), splitted_by_punc.begin(), splitted_by_punc.end());
    }

    vector<wstring> wordpiece_tokenized;
    for (size_t i = 0; i < basic_tokenized.size(); i++)
    {
      auto splitted_by_wordpiece = wordpiece_tokenize(basic_tokenized[i]);
      wordpiece_tokenized.insert(wordpiece_tokenized.end(), splitted_by_wordpiece.begin(), splitted_by_wordpiece.end());
    }

    vector<int64_t> tokenized_ids;
    tokenized_ids.push_back(get_word_index(utf8_to_wstring("[CLS]")));
    vector<int64_t> seq_ids = convert_tokens_to_ids(wordpiece_tokenized);
    tokenized_ids.insert(tokenized_ids.end(), seq_ids.begin(), seq_ids.end());
    tokenized_ids.push_back(get_word_index(utf8_to_wstring("[SEP]")));
    return tokenized_ids;
  }

  vector<wstring> wordpiece_tokenize(const wstring &input_text)
  {
    vector<wstring> tokens = split(input_text);
    vector<wstring> output_tokens;
    for (size_t i = 0; i < tokens.size(); i++)
    {
      auto &tok = tokens[i];
      if (tok.length() > max_input_chars_per_word)
      {
        output_tokens.push_back(unk_token);
        continue;
      }

      bool is_bad = false;
      size_t start = 0;
      vector<wstring> sub_tokens;

      while (start < tok.length())
      {
        size_t end = tok.length();
        wstring cur_substr;
        while (start < end)
        {
          wstring substr = tok.substr(start, end - start);
          if (start > 0)
          {
            substr = L"##" + substr;
          }
          size_t idx = get_word_index(substr);
          if (idx != -1)
          {
            cur_substr = substr;
            break;
          }
          end--;
        }

        if (cur_substr.empty())
        {
          is_bad = true;
          break;
        }
        sub_tokens.push_back(cur_substr);
        start = end;
      }

      if (is_bad)
      {
        output_tokens.push_back(unk_token);
      }
      else
      {
        output_tokens.insert(output_tokens.end(), sub_tokens.begin(), sub_tokens.end());
      }
    }
    return output_tokens;
  }

  vector<int64_t> convert_tokens_to_ids(const vector<wstring> &input_seq)
  {
    vector<int64_t> output_ids;
    for (size_t i = 0; i < input_seq.size(); i++)
    {
      output_ids.push_back(get_word_index(input_seq[i]));
    }
    return output_ids;
  }
};

std::vector<int64_t> tokenize(const std::string &input_text)
  {

    std::wstring wide_input_text = utf8_to_wstring(input_text);
    WordPieceTokenizer tokenizer(tknzierJson);
    std::vector<int64_t> token_ids = tokenizer.tokenize_full(wide_input_text);
    return token_ids;
  }

int main() {
    std::string input_text = "austin is capital of texas";
    std::vector<int64_t> token_ids = tokenize(input_text);

    std::cout << "Token IDs: ";
    for (const auto& id : token_ids) {
      std::cout << id << " ";
    }
    std::cout << std::endl;

    return 0;
}

