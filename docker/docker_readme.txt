# 

1. Выкачиваем minimal-versions.
git clone <url_to_minimal-versions>

2. Скачиваем Docker-образы: dev - для сборки и runtime - для запуска.
docker pull <url_to_docker-image/DEV>
docker pull <url_to_docker-image/RT>

3. В minimal-versions/profiles создаю скрипт project_name.py и папку project_name.
3.1. Папка project_name должна содержать файл parameters.yaml и папку workspace.
     Здесь же кладутся все необходимые файлы, бинари, конфиги, монтируются тома и т.д.

4. Когда вся логика имплементирована в папке project_name, переходим в папку minimal-versions,
   запускаем скрипт generate_version.py.
./generate_version.py project_name

5. Переходим в папку minimal-versions/versions. Здесь лежит сгенерированный архив и *.yaml-файл.
5.1. Распаковываем архив и в папке scripts запускаем interactive_start.sh.

6. Изменения в ветке пушим реквестом в gitlab.
