# Password-Generator  
A simple Password Generator for Windows 

![image](https://github.com/user-attachments/assets/d50711c2-b9e0-4117-8313-ce641da2578c) 

It contains four random combinations：
- upper alphabet (A-Z)
- lower alphabet (a-z)
- digits (0-9)
- symbols (!@#$%^&*()_+~`|}{[]:;?><,./-=)  

## get ready
- you need to make sure the tools of make and cmake works
- it depends on projects [FTLK](https://github.com/fltk/fltk/)
	```bash
     cmake . -B build -G "MinGW Makefiles" --fresh
     cmake --build build
     cmake --install build --prefix="your FLTK path" 
    ```

- icon.rc
  ```bash
  168 ICON "yours.ico"
  ```
- icon.o
  ```bash
  windres -i icon.rc -o icon.o --target=pe-x86-64  
  ```
## build
```
g++ pg_gui.cpp icon.o -o password_generator -std=c++14 -I "your FLTK path /include" -L "your FLTK path /lib" -lfltk -lfltk_images -lgdiplus -lws2_32 -lwinspool -lole32 -luuid -lcomctl32 -lgdi32 -mwindows
```
