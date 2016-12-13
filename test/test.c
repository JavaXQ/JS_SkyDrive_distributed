#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include"make_log.h"
#include"file_upload.h"

int main(int argc, char* argv[])
{
	char *buf;

	if(file_upload(argc, argv, (void**)&buf) < 0)
	{
		exit(1);
	}

	LOG("test", "fdfs", "file_id = [%s]", buf);

	free(buf);
	buf = NULL;

	return 0;
}
