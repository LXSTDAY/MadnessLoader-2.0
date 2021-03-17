from ftplib import FTP

ftp = FTP()
HOST = '192.168.0.100'
PORT = 2121
ftp.connect(HOST, PORT)
ftp.login()

nameplugin = input('Write name plugin without .so: ')

ftp.cwd('Download')

# Открываем файл для передачи в бинарном режиме
f = open("C:\\Android/MadnessLoader-2.0/libs/armeabi-v7a/lib" + nameplugin + ".so", "rb")
# Передаем файл на сервер
ftp.storbinary('STOR '+nameplugin+".pm", f, f.__sizeof__())
# Закрываем FTP соединение

print('file "' + nameplugin + '.pm" in Download folder created!')
ftp.close