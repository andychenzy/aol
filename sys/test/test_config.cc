
#include <stdint.h>

#include <aol_config.h>

using namespace aolsys;
using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "Usage: %s configure_name\n", argv[0]);
    return -1;
  }

  if (AOL_CONFIG.load(argv[1])) {
    fprintf(stderr, "Load config failure: %s\n", argv[1]);
    return -1;
  }

  fprintf(stderr, "String = %s\n", AOL_CONFIG.getString("test_section", "string"));
  fprintf(stderr, "Int = %d\n", AOL_CONFIG.getInt("test_secion", "int"));

  vector<const char*> strList = AOL_CONFIG.getStringList("test_section", "stringlist");
  for (int i = 0; i < (int)strList.size(); i++) {
    fprintf(stderr, "string %d = %s\n", i + 1, strList[i]);
  }

  vector<int> intList = AOL_CONFIG.getIntList("test_section", "intlist");
  for (int i = 0; i < (int)intList.size(); i++) {
    fprintf(stderr, "int %d = %d\n", i + 1, intList[i]);
  }

  vector<string> keys;
  AOL_CONFIG.getSectionKey("test_section", keys);
  for (int i = 0; i < (int)keys.size(); i++) {
    fprintf(stderr, "Key_%d = %s\n", i + 1, keys[i].c_str());
  }

  fprintf(stderr, "\nconfig str:\n%s\n", AOL_CONFIG.toString().c_str());

  return 0;
}

