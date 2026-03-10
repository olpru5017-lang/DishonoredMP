# DishonoredMP

Auto-loaded co-op mod bootstrap for Dishonored using a `dinput8.dll` proxy.

## Почему у тебя не работало раньше

`dishonored_mp.dll` как отдельный файл игра не обязана загружать сама.
Нужна точка автозагрузки. В этой версии используется стандартный proxy-механизм через `dinput8.dll`.

## Быстрый старт (одна команда)

```bash
./scripts/make_one_file.sh
```

Результат:
- `dist/dishonored_mp_package.zip`

Внутри:
- `dinput8.dll` (Windows) / `libdinput8.so` (контейнерный Linux-билд)
- `dishonored_mp.cfg`
- `INSTALL.txt`

## Установка в игру (Win32)

1. Скопируй `dinput8.dll` в `Dishonored\Binaries\Win32`.
2. Скопируй `dishonored_mp.cfg` рядом.
3. Запусти игру.
4. Проверь `dishonored_mp.log` — там должна быть строка про загрузку через dinput8 proxy.

## Важно

- Если у тебя уже есть другой `dinput8.dll` (другой мод/лоадер), нужен chain-load.
- `dxgi.dll` (например ReShade) не гарантирует загрузку `dishonored_mp.dll`, если специально не настроен чейн.
- Адреса engine hooks пока заглушки — для реального UI-injection в меню нужны точные оффсеты под твою версию Dishonored.
