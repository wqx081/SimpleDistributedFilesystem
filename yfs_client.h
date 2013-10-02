#ifndef yfs_client_h
#define yfs_client_h

#include <list>
#include <string>
#include <vector>

//#include "yfs_protocol.h"
#include "extent_client.h"

// ELEMENTSEPERATOR - what seperates elements in a inode, eg /sub_dir1/sub_dir2/file1/file2
// INUMSEPERATOR    - what seperates an elements name from its inum, eg inum@elementname
// So an example of a directory listing would be: 1234@subdirectory/1235@filename/

#define ELEMENTSEPERATOR '/'
#define INUMSEPERATOR    '@'

class yfs_client {
  extent_client *ec;
 public:

  typedef unsigned long long inum;
  enum xxstatus { OK, RPCERR, NOENT, IOERR, EXIST };
  typedef int status;

  struct fileinfo {
    unsigned long long size;
    unsigned long atime;
    unsigned long mtime;
    unsigned long ctime;
  };
  struct dirinfo {
    unsigned long atime;
    unsigned long mtime;
    unsigned long ctime;
  };
  struct dirent {
    std::string name;
    yfs_client::inum inum;
  };

 private:
  static inum n2i(std::string);
  static std::string filename(inum);
  static void split(const std::string &, char, std::list<std::string> &);
 public:

  yfs_client(std::string, std::string);

  bool isfile(inum);
  bool isdir(inum);

  int getfile(inum, fileinfo &);
  int getdir(inum, dirinfo &);

  int createFile(inum &, inum, const char*);
  int lookupResource(yfs_client::inum &, yfs_client::inum, const char*);
  int getDirContents(yfs_client::inum, std::string &);

  std::string createBuffElement(yfs_client::inum, const char*);
  std::list<yfs_client::dirent*>* parsebuf(std::string);
  dirent* parseDirent(std::string);
};

#endif
