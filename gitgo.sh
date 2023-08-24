git status
echo "Перейти к add & commit? (y/n)\n"
if [[ "$1" == "y" ]]; then
    git add .
    echo "Введите сообщение для коммита\n"
    git commit -m "$*"
   
else
    echo "Finished"
fi