#ifndef _PCS_SHELL_DIR_H_
#define _PCS_SHELL_DIR_H_

#define DEFAULT_MKDIR_ACCESS	0750	/*创建目录时默认权限，只有非Windows系统使用*/

#define MKDIR_OK				0		/*目录创建成功*/
#define MKDIR_FAIL				1		/*目录创建失败*/
#define MKDIR_TARGET_IS_FILE	2		/*本地存在，且是文件*/


typedef struct LocalFileInfo LocalFileInfo;

struct LocalFileInfo
{
   char				*path;
   const char		*filename;
   int				isdir;
   time_t			mtime;
   size_t			size;
   LocalFileInfo	*parent;
   LocalFileInfo	*next;

   void				*userdata;
};

/*释放掉LocalFileInfo对象*/
void DestroyLocalFileInfo(LocalFileInfo *info);

/*释放掉LocalFileInfo链表*/
void DestroyLocalFileInfoLink(LocalFileInfo *link);

/*
* 获取指定文件或目录的信息
*  file  - 文件或目录的路径
* 如果文件或目录不存在，则返回NULL；否则返回其LocalFileInfo对象。
*/
LocalFileInfo *GetLocalFileInfo(const char *file);

/*
* 获取dir目录下的所有文件或目录。
*   dir       - 目标目录路径
*   recursion - 是否递归列出
*   on        - 当获取到一个对象后的回调函数
*      回调函数参数：
*       info   - 当前获取到的文件
*       parent - 当前获取到的文件的父目录
*       state  - 状态值，有用户传入
*   state     - 要传递到回调函数第三个参数的值
* 成功后返回一个LocalFileInfo链表
*/
LocalFileInfo *GetDirectoryFiles(const char *dir, int recursive, 
	void(*on)(LocalFileInfo *info, LocalFileInfo *parent, void *state), void *state);

/*设置文件的最后修改时间。
如果执行成功则返回0，
否则返回非0值。*/
int SetFileLastModifyTime(const char *file, time_t mtime);

/*
* 递归创建目录
*    path - 待创建的目录
* 如果成功则返回MKDIR_OK，否则返回错误码，可能错误码有: MKDIR_FAIL, MKDIR_TARGET_IS_FILE。
*/
int CreateDirectoryRecursive(const char *path);



#endif
