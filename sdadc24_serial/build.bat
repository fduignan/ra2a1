arm-none-eabi-gcc -std=c++17 -static -mthumb -g -mcpu=cortex-m23 *.cpp -T linker_script.ld -o main.elf  -fno-rtti  -fno-exceptions -nostartfiles -Xlinker -Map=output.map 
arm-none-eabi-objcopy -g -O ihex main.elf main.hex 
