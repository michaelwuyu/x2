# Come Alive Again !
> X2 重新进入开发阶段

> Francis Bach Blesses All the Old People !!!!

# X2
作为一个软件设计项目而产生的操作系统，能够运行在x86架构,ARM上（树莓派）

其中移植了STLPort作为C++库(TODO)

# 查看完整的帮助文档
对于技术类的文档，请查看Manuals文件夹


# 源代码说明
源代码在include和src两个文件夹下, include存放设计说明,src存放实现

# 开发者提示
此工程使用的是eclipse作为首选开发工具，因此通过eclipse的引入即可得到一个完整的工程。eclipse版本见版本号一节。

此外，所有的代码看起来都很易懂，但是加在一起就失去了它们原来的含义。

设计是万物的原动力，而人生必经两件事：死亡和重构。
# 关于重构
重构到底是代码功底不成熟的表现还是软件本身固有的易变性，此处不讨论。X2的代码原则是易重构的，有数条原则严格施行来保证这种易重构性，包括：

1. 命名机制：以\_\_开头的属于私有空间，私有空间指的是：类的作用域，类的成员函数实现的文件局部以及其他将来可能添加为私有空间的作用域，其次，宏的作用也相当重要，没有宏c++就失去了一半的简易性和一半的灵活性。所有的宏私有名称以\_\_DEF\_开头，并且使用完毕即#undef取消定义

2. 所有需要使用模板的地方，使用局部无模板名称替代

3. 避免任何需要手动生成的代码，譬如模板实例化
```template class Foo<Bar>;```， 让编译器自己去推断它用到的那些类型并自动生成代码。

# ISO-C++语言标准 和 GNU-g++编译器
现在添加了对标准库的部分文件注释，参见Manuals下ISO\_c++.md 和  GNU_g++.md两个文件

# 测试和编译工具链版本号
这里列出一些有效的测试和编译工具版本号，它们已经成功地编译了可运行的镜像文件

已经测试的编译环境：cygwin 2.881

- eclipse	neon.3 { aka 4.6.2 }
- gcc	6.4.0
- g++	6.4.0
- as	2.29.1.20171006
- ld	2.29.1.20171006
- objcopy	2.29.1.20171006
- objdump	2.29.1.20171006
- ar	2.29.1.20171006
- dd	8.26
- rm	8.26(抱歉，我是认真地把所有用到的工具写上)
- mkdir	8.26
- cp	8.26
- echo	8.26
- make	4.2.1
- bochs	2.6.9
- git	2.15.0
- tar	1.29

