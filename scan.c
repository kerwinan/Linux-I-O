#include <stdio.h>  
#include <sys/types.h>  
#include <string.h>  
#include <dirent.h>  
  
int scan_dir(char *path)  
{  
    DIR *p_dir;  
    struct dirent *p_dirent;  
    char buff[256] = {0};  
    //调用 umask 函数设置文件的默认创建权限掩码  
    umask(0);  
    //调用 access 判断目录是否存在  
    if (access("./dir", F_OK)){  
        //如目录不存在则调用 mkdir 函数创建目录  
        mkdir("./dir", 0777);  
    }  
    //调用 opendir 函数打开目录，返回目录流指针  
    p_dir = opendir(path);  
    if (NULL == p_dir){  
      printf("opendir error!\n");  
      return -1;  
    }         
    //调用 readdir 函数，通过对目录流指针的操作来循环读取目录内容，  
    //返回文件内容（inode 节点，文件名称，文件类型等等）  
    while ((p_dirent = readdir(p_dir)) != NULL){  
        if (!strcmp(p_dirent->d_name, ".") || !strcmp(p_dirent->d_name, ".."))  
          continue;          
        if (path[strlen(path) - 1] != '/'){  
            strcat(path, "/");  
        }  
        sprintf(buff, "%s%s", path, p_dirent->d_name);  
        if (p_dirent->d_type == DT_DIR){  
            //进入目录继续查看  
            scan_dir(buff);  
        }else{  
            printf("file:[%s] is file\n", p_dirent->d_name);  
        }  
    }  
    //调用 closedir 函数关闭目录  
    closedir(p_dir);  
}  
  
int main(int argc, char* argv[])  
{  
    char path[256] = "./dir";  
    scan_dir(path);  
    return 0;  
}  