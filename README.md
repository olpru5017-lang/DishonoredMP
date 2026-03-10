# DishonoredMP

Single-DLL host-authoritative co-op multiplayer mod framework for Dishonored.

## Быстрый старт (одна команда)

Чтобы не вводить вручную `cmake ...`, используй:

```bash
./scripts/make_one_file.sh
```

На выходе получишь один готовый архив:

- `dist/dishonored_mp_package.zip`

Внутри:
- `dishonored_mp.dll` (на Windows-сборке) или `libdishonored_mp.so` (в Linux-контейнере)
- `dishonored_mp.cfg`
- `INSTALL.txt`

## Что делает DLL

- Авто-инициализируется при загрузке игры
- Подгружает `dishonored_mp.cfg`
- Регистрирует runtime hooks
- Добавляет кнопку **Multiplayer** в главное меню рядом с обычными пунктами кампании

## Ручная сборка (если нужно)

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Notes

- Hook addresses are placeholders and should be mapped to your Dishonored build.
- Transport backend can be swapped to ENet/SteamNetworking in networking layer.
