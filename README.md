<div align="center">

# ⚡ Fastfetch on C

**Минималистичная и молниеносная утилита для мониторинга системы, написанная на чистом C.**

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Linux-lightgrey.svg)]()
[![Arch Linux](https://img.shields.io/badge/Arch_Linux-1793D1?logo=arch-linux&logoColor=white)]()
[![Version](https://img.shields.io/badge/Version-v0.1-green.svg)]()

</div>

---

## 📖 О проекте

`Fastfetch on C` — это учебный проект, созданный с нуля без использования сторонних библиотек. Программа напрямую взаимодействует с виртуальной файловой системой ядра Linux (`/proc`), извлекая и парся данные о вашем железе. 

Проект создан для оттачивания навыков работы с файлами (`fopen`, `fgets`), парсинга строк (`sscanf`, `strstr`) и управления памятью в языке C.

## ✨ Возможности

На данный момент утилита считывает и выводит:
* 🧠 **CPU** — Модель процессора (из `/proc/cpuinfo`).
* 💾 **RAM** — Общий объем оперативной памяти в гигабайтах (из `/proc/meminfo`).
* 🐧 **Distro** — Название вашего дистрибутива Linux (из `/etc/os-release`).
* ⏳ **Uptime** — Время прошедшее с момента запуска устройства (из `/proc/uptime`).

## 📸 Демонстрация

Вот как выглядит вывод программы в терминале:

```text
CPU: Intel(R) Core(TM) i5-10400F CPU @ 2.90GHz
RAM: 23.36 GB
Distro: Arch Linux
Uptime: 0 hours, 31 mins
```

## 🚀 Установка и запуск

Для сборки вам потребуется компилятор **GCC** (стандартный для Linux).

**1. Клонируйте репозиторий:**
```bash
git clone https://github.com/ent1ty-404/fastfetch-on-C-v0.1.git
cd fastfetch-on-C-v0.1
```

**2. Скомпилируйте исходный код:**
```bash
gcc fastfetch-on-c.c -o fastfetch-on-c
```

**3. Запустите утилиту:**
```bash
./fastfetch-on-c
```

## 🗺️ Планы по развитию (Roadmap)

- [x] Вывод информации о процессоре.
- [x] Вывод информации об ОЗУ (с конвертацией в ГБ).
- [x] Вывод названия дистрибутива.
- [X] Добавить вывод Uptime (время работы системы с момента включения).
- [ ] Добавить вывод модели видеокарты (GPU) через `nvidia-smi`.
- [ ] Добавить вывод имени пользователя (`getenv`).
- [ ] Разноцветный вывод в терминале с помощью ANSI-кодов.
- [ ] Добавить красивый ASCII-арт логотипа дистрибутива.

## 👨‍💻 Автор

**ent1ty-404** 
* GitHub: [@ent1ty-404](https://github.com/ent1ty-404)
* Начинающий C-разработчик и линуксоид.

---
<div align="center">
  <i>Если тебе понравился проект, поставь звезду ⭐ на GitHub!</i>
</div>
