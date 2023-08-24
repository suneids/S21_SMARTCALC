git status
echo "Перейти к add & commit? (y/n)"
read -r answer
if [[ $answer == "y" ]]; then
    git add .
    echo "Введите сообщение для коммита"
    read -r message
    git commit -m "$message"
else
    echo "Finished"
fi