git status
echo "Перейти к add & commit? (y/n)"
read -r answer
if [[ $answer == "y" ]]; then
    git add .
    echo "Введите сообщение для коммита"
    read -r message
    git commit -m "$message"
    read -r answer
    echo "Перейти к push? (y/n)"
    if [[ $answer == "y" ]]; then
        echo "Введите ветку"
	read -r branch
        git push $branch
    fi	
else
    echo "Finished"
fi