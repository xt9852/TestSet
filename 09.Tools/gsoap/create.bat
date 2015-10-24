@rem -s不使用STL代码 -o指定输出文件 -t mytypema.dat可设置字符串类型  WebService地址

wsdl2h.exe  -s -o Service.h http://www.webxml.com.cn/WebServices/ChinaStockWebService.asmx
soapcpp2.exe Service.h