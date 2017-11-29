
 //CODE64 ONLY
#include <File.h>

#if !defined(CODE64)
#error "CODE64 ONLY"
#endif

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>

#include <List.h>

#if defined(CODE64)

#define SECNUM 100
#define IMG_SIZE SECNUM*X2fsUtil::SecSize
/**
 * 开辟一个内存块，格式化，然后将其保存到文件中作为磁盘。
 */
int main(int argc,char *argv[])
{

	const char *filestr;
	if(argc<2)
	{
		std::string filename;
		std::cout << "please input a file:";
		std::cin >> filename;
		filestr = filename.c_str();
	}else{
		filestr = argv[1];
	}
	EnvInterface64Impl *envInstance=EnvInterface64Impl::getInstance(filestr);

	X2fsMetaInfo<size_t> metainfo;
	metainfo.lbaStartLow = 0x3000;
	metainfo.lbaStartHigh = 0;
	metainfo.wholeSecnums = 8192;
	metainfo.secnums[X2fsMetaInfo<size_t>::INDEX_NAME]=X2fsUtil<EnvInterface64Impl,size_t>::FileNameSectionLen/CONST_SECSIZE;
	metainfo.secnums[X2fsMetaInfo<size_t>::INDEX_DIR]=X2fsUtil<EnvInterface64Impl,size_t>::DirSectionLen/CONST_SECSIZE;
	metainfo.secnums[X2fsMetaInfo<size_t>::INDEX_FREE]=X2fsUtil<EnvInterface64Impl,size_t>::FreeSpaceSectionLen/CONST_SECSIZE;
	metainfo.secnums[X2fsMetaInfo<size_t>::INDEX_LINK]=X2fsUtil<EnvInterface64Impl,size_t>::LinkedInfoSectionLen/CONST_SECSIZE;
	metainfo.optional[X2fsMetaInfo<size_t>::INDEX_OPTIONAL_SECD]=0;

	std::cout << "information about metainfo"<<std::endl;
	metainfo.dumpInfo(envInstance);
	std::cout << std::endl;

	if(!X2fsMetaInfo<size_t>::checkMetainfo(&metainfo))
		printf("cannot validate metainfo\n");
	else
		X2fsUtil<EnvInterface64Impl,size_t>::mkfs(envInstance, 0x80, &metainfo);

	printf("re-reading the information to validate....");
//	X2fsMetaInfo *buf=(X2fsMetaInfo*)env->malloc(sizeof(X2fsMetaInfo));
//	X2fsMetaInfo *buf = new X2fsMetaInfo;
	u8_t *buf = envInstance->malloc(metainfo.metaSec * CONST_SECSIZE);
	X2fsMetaInfo<size_t> *readMetainfo=(X2fsMetaInfo<size_t>*)buf;
	envInstance->readSectors(EnvInterface::CUR_SEG, buf,0x80,0x3000+2, 1, 0);
	if(!X2fsMetaInfo<size_t>::checkMetainfo(readMetainfo))
	{
		printf("validating failed!\n");
	}else{
		printf("validating succeed!\n");
	}
	envInstance->flushOutputs();


	envInstance->free(buf);

	printf("end.\n");
	envInstance->flushOutputs();
}

#endif
