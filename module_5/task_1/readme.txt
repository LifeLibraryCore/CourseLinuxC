#Вставка модуля в ядро.
insmod task_1.ko
dmesg | tail -1
#Удаление модуля из ядра.
rmmod task_1.ko
dmesg | tail -1
