![Philosophers logo](.media/philosophers_logo.png)

![Grade badge](https://img.shields.io/badge/00_%2F_100-004d40?label=final%20grade&labelColor=151515&logo=data:image/svg%2bxml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIGhlaWdodD0iMjRweCIgdmlld0JveD0iMCAwIDI0IDI0IiB3aWR0aD0iMjRweCIgZmlsbD0iI0ZGRkZGRiI+PHBhdGggZD0iTTAgMGgyNHYyNEgweiIgZmlsbD0ibm9uZSIvPjxwYXRoIGQ9Ik0xMiAxNy4yN0wxOC4xOCAyMWwtMS42NC03LjAzTDIyIDkuMjRsLTcuMTktLjYxTDEyIDIgOS4xOSA4LjYzIDIgOS4yNGw1LjQ2IDQuNzNMNS44MiAyMXoiLz48L3N2Zz4=) ![Language Badge](https://img.shields.io/badge/C-fe428e?logo=C&label=language&labelColor=151515) ![Norminette Badge](https://img.shields.io/badge/passing-brightgreen?logo=42&label=norminette&labelColor=151515) ![Library Badge](https://img.shields.io/badge/none-c40233?logo=GitHub&label=library%20used&labelColor=151515)

# Philosophers 🧠

Ce projet concerne le multithreading : le programme simule un dîner entre un groupe de philosophes `nbr_of_philo`. Ils partagent un bol de spahghetti au milieu de la table et une fourchette par personne.
Une fourchette est placée entre chaque philosophe ; un philosophe ne peut manger qu'avec l'aide des deux fourchettes à sa gauche et à sa droite.
Le mutex doit être utilisé pour verrouiller les fourchettes de chaque philosophe afin d'éviter qu'ils ne se volent les fourchettes des autres.
Une fois qu'un philosophe a mangé pendant `time_to_eat` millisecondes, il commence à dormir pendant `time_to_sleep` millisecondes puis commence à réfléchir. Il réfléchit aussi longtemps qu'il le peut mais au moins 2 millisecondes.
Si un philosophe n'a pas commencé à manger depuis `time_to_die` millisecondes après le début de la simulation ou le début de son dernier repas, il meurt.
Le programme affiche le journal de simulation selon le format suivant :
* `timestamp_in_ms` `X` has taken a fork
* `timestamp_in_ms` `X` is eating
* `timestamp_in_ms` `X` is sleeping
* `timestamp_in_ms` `X` is thinking
* `timestamp_in_ms` `X` died

Vous trouverez le sujet [ici](en.subject.pdf)
