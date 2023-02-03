# 原神双端登陆器（3.4）
目前原神PC端官服和B服的相互切换较为繁琐，如果不想下载两遍游戏，则需要修改配置文件，此软件提供了一个修改配置文件便捷方法。  
  
## 使用方法：
需要下载官服和B服的启动器，且用B服登录过游戏（用于生成`PCGameSDK.dll`文件）  
随后按软件提示输入对应的启动路径就行了  
  
  
## 原理：
B服转官服：
  1. 删除`D:\Genshin Impact Game\YuanShen_Data\Plugins\PCGameSDK.dll`文件
  2. 修改`D:\Genshin Impact Game\config.ini`文件，令`channel=1`，`cps=mihoyo`
官服转B服：
  1. 添加`D:\Genshin Impact Game\YuanShen_Data\Plugins\PCGameSDK.dll`文件
  2. 修改`D:\Genshin Impact Game\config.ini`文件，令`channel=14`，`cps=bilibili`
  
## 下载地址
[点击此处](https://github.com/jusaclown/yuanshen_launcher/releases/download/3.4/yuanshen.rar)下载


## 问题：
无法保留官服的登录信息，每次都需重新输入账号密码
