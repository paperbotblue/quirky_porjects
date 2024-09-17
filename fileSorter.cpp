#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

struct File {
  std::string name;
  std::string extention;
};


// add as many formates as you like and don't forget to increment the array size
struct folder_types {
  std::string photos[5] = {".jpg", ".png", ".bmp", ".dng", ".jpeg"};
  std::string videos[1] = {".mp4"};
  std::string audio[3] = {".mp3", ".aac", ".wav"};
  std::string documents[4] = {".pdf", ".odg", ".docx", ".txt"};
};
folder_types folders;

File get_file(std::string file_name);
int get_type(std::string extention);

int main(int argc, char **argv) {
  File file;

  //dir to sort into if they arn't made in the folder you run this then the program won't work
  std::string photos = "./photos/";
  std::string videos = "./videos/";
  std::string audio = "./audio/";
  std::string documents = "./documents/";
  std::string others = "./others/";

  try {
    for (auto const &dir_entry : fs::directory_iterator{argv[1]}) {
      if(dir_entry.is_directory()) continue;

      file = get_file(dir_entry.path());
      std::cout << dir_entry.path() << "\n";
      switch (get_type(file.extention)) {
      case 0:
        fs::copy_file(dir_entry.path(), photos + "'" + file.name + file.extention + "'");
        fs::remove(dir_entry.path());
        break;
      case 1:
        fs::copy_file(dir_entry.path(), videos + "'" + file.name + file.extention + "'");
        fs::remove(dir_entry.path());
        break;
      case 2:
        fs::copy_file(dir_entry.path(), audio + "'" + file.name + file.extention + "'");
        fs::remove(dir_entry.path());
        break;
      case 3:
        fs::copy_file(dir_entry.path(), documents + "'" + file.name + file.extention + "'");
        fs::remove(dir_entry.path());
        break;
      case 4:
        fs::copy_file(dir_entry.path(), others + "'" + file.name + file.extention + "'");
        fs::remove(dir_entry.path());
        break;
      }
    }
  } catch (fs::filesystem_error &e) {
    std::cout << e.what() << "\n";
  }
  return 0;
}

int get_type(std::string extention) {
  for (auto type : folders.photos) {
    if (extention == type)
      return 0;
  }
  for (auto type : folders.videos) {
    if (extention == type)
      return 1;
  }
  for (auto type : folders.audio) {
    if (extention == type)
      return 2;
  }
  for (auto type : folders.documents) {
    if (extention == type)
      return 3;
  }
  return 4;
}

File get_file(std::string file_name) {
  File file;
  bool extention_flag = false;
  for (int i = 2; i < file_name.length(); ++i) {
    if (file_name.at(i) == '.' || extention_flag) {
      extention_flag = true;
      file.extention += file_name.at(i);
    }
    if (!extention_flag)
      file.name += file_name.at(i);
  }
  return file;
}