<div align="center">

# ⚡ Fastfetch on C

**Минималистичная и молниеносная утилита для мониторинга системы, написанная на чистом C.**

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Arch_Linux-1793D1?logo=arch-linux&logoColor=white)]()
[![Version](https://img.shields.io/badge/Version-1.0-green.svg)]()
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

</div>

---

## 📖 О проекте

`Fastfetch on C` — это учебный проект, созданный с нуля без использования сторонних библиотек. Программа напрямую взаимодействует с виртуальной файловой системой ядра Linux (`/proc`, `/etc`, `/sys`), извлекая и парся данные о вашем железе, а также использует системные вызовы (`statvfs`) и утилиты командной строки (`hyprctl`, `nvidia-smi`).

Проект создан для оттачивания навыков работы с файлами (`fopen`, `fgets`), парсинга строк (`sscanf`, `strstr`, `strrchr`), управления памятью и запуска внешних процессов (`popen`) в языке C. **Версия 1.0** — это стабильный релиз, который включает в себя все запланированные функции.

## ✨ Возможности

Утилита собирает и выводит следующую информацию:

*   🧠 **CPU**: Модель процессора (из `/proc/cpuinfo`).
*   💾 **RAM**: Общий объём оперативной памяти в гигабайтах (из `/proc/meminfo`).
*   🎮 **GPU**: Модель видеокарты (через `nvidia-smi`).
*   🐧 **Distro**: Название дистрибутива Linux (из `/etc/os-release`).
*   👤 **User**: Имя текущего пользователя (переменная окружения `USER`).
*   🐚 **Shell**: Текущая оболочка (переменная окружения `SHELL`).
*   🖥️ **WM/DE**: Оконный менеджер (переменная окружения `XDG_CURRENT_DESKTOP`).
*   📺 **Monitor**: Модель монитора и его разрешение/частота (через `hyprctl monitors`).
*   💽 **Disk (/)**: Информация о корневом разделе (через `statvfs`).
*   💾 **EFI**: Информация о загрузочном EFI-разделе (через `statvfs`).
*   ⚙️ **Kernel**: Версия ядра Linux (из `/proc/version`).
*   ⏳ **Uptime**: Время работы системы (из `/proc/uptime`).

## 📸 Демонстрация

Вывод программы в терминале (с цветовым оформлением в стиле Arch Linux):

```text
CPU: Intel(R) Core(TM) i5-10400F CPU @ 2.90GHz
RAM: 23.36 GB
GPU: NVIDIA GeForce RTX 3050
Distro: Arch Linux
User: arch-enti
Shell: fish
Disk(/): 166.77 GiB / 467.91 GiB (36%)
EFI: 152.87 MiB / 487.00 MiB (31%)
WM/DE: Hyprland
Monitor: Xiaomi Corporation P27FBB-RGGL 5275600000663
Mode: 1920x1080@165.00200
Kernel: 7.2.11-arch1-1
Uptime: 1 hours, 28 mins
```

## 🚀 Установка и запуск

Для сборки вам потребуется компилятор **GCC** (стандартный для Linux).

**1. Клонируйте репозиторий:**
```bash
git clone https://github.com/ent1ty-404/fastfetch-on-C.git
cd fastfetch-on-C
```

**2. Скомпилируйте исходный код:**
```bash
gcc fastfetch-on-c.c -o fastfetch-on-c
```

**3. Запустите утилиту:**
```bash
./fastfetch-on-c
```

## ⚠️ Требования и совместимость

> [!IMPORTANT]
> Проект разрабатывается и тестируется **исключительно** в среде **Arch Linux** с оконным менеджером **Hyprland**.

> [!WARNING]
> Для работы функции `GPU()` **обязательна** видеокарта **NVIDIA** и наличие утилиты `nvidia-smi`. На системах с Intel/AMD или без проприетарных драйверов NVIDIA этот блок выведет ошибку.
>
> Для работы функции `Monitor()` требуется активная сессия **Hyprland** (используется команда `hyprctl`).

## 🗺️ Планы по развитию (Roadmap)

Проект завершён (v1.0),

- [x] Вывод информации о процессоре.
- [x] Вывод информации об ОЗУ (с конвертацией в ГБ).
- [x] Вывод названия дистрибутива.
- [x] Добавить вывод Uptime.
- [x] Добавить вывод модели видеокарты (GPU).
- [x] Добавить вывод имени пользователя и оболочки.
- [x] Добавить вывод информации о дисках (`statvfs`).
- [x] Добавить вывод версии ядра.
- [x] Добавить вывод модели монитора (через `hyprctl`).
- [x] Добавить цветной вывод (ANSI-коды) в стиле Arch Linux.

## 👨‍💻 Автор

**ent1ty-404** 
* GitHub: [@ent1ty-404](https://github.com/ent1ty-404)
* Начинающий C-разработчик.

---
<div align="center">
  <i>Если тебе понравился проект, поставь звезду ⭐ на GitHub!</i>
</div>
