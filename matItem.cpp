#include <iostream>
#include <fstream>
#include <string>
#include "json.h"
using namespace std;
using namespace json;

int main(int argc, char** argv){

for(int k = 1; k< argc; k++){

  ofstream output_file;
  string* newfile = new string(argv[k]);
  
  output_file.open(newfile->erase((newfile)->rfind(".material"), 9999) += ".matitem"); 
FILE* f = fopen(argv[k], "r");

   // Determine file size
   fseek(f, 0, SEEK_END);
   size_t size = ftell(f);

   char* data = new char[size];
 data[size] = 0;
   rewind(f);
   fread(data, sizeof(char), size, f);
   fclose(f);
   const std::string str(data, data + strlen(data));
Object json_file = Deserialize(str).ToObject();

json_file["itemName"] = json_file["itemDrop"];
json_file.erase("materialName");
json_file["inventoryIcon"] = json_file["frames"];
json_file.erase("frames");
json_file.erase("itemDrop");
json_file.erase("health");
json_file.erase("particleColor");
json_file.erase("footstepSound");
json_file.erase("variants");
json_file.erase("multicolored");
json_file.erase("damageTable");
json_file["dropCollision"] = Deserialize("[-2.5, -2.0, 2.5, 2.0]");
json_file["rarity"] = "Common";


string serialized = Serialize(json_file);
   
   output_file << serialized;
   output_file.close();
   }



}
