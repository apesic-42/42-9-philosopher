## 🧾 Ligne de commande

Le programme se lance comme ceci :

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Tu dois passer **4 ou 5 arguments**.

---

## 🧠 Signification des arguments

| Argument                                      | Type                | Description                                                                              |
| --------------------------------------------- | ------------------- | ---------------------------------------------------------------------------------------- |
| `number_of_philosophers`                      | **int**             | Nombre de philosophes **(et de fourchettes)** autour de la table                         |
| `time_to_die`                                 | **ms**              | Temps maximum qu’un philosophe peut passer **sans manger**, sinon il **meurt**           |
| `time_to_eat`                                 | **ms**              | Temps qu’un philosophe passe à **manger** (pendant ce temps, il garde les 2 fourchettes) |
| `time_to_sleep`                               | **ms**              | Temps qu’un philosophe passe à **dormir** après avoir mangé                              |
| `[number_of_times_each_philosopher_must_eat]` | **int (optionnel)** | Si fourni : la simulation s’arrête **quand chaque philosophe a mangé ce nombre de fois** |

---

## 🎯 Exemples

### ➤ Exemple 1 : classique

```bash
./philo 5 800 200 200
```

* 5 philosophes
* Chacun meurt s’il ne mange pas dans les 800ms
* Manger prend 200ms
* Dormir prend 200ms
* **La simulation continue jusqu'à ce qu'un philosophe meure**

---

### ➤ Exemple 2 : avec condition d’arrêt

```bash
./philo 4 410 200 200 3
```

* 4 philosophes
* Chacun meurt au bout de 410ms sans manger
* Ils mangent 200ms et dorment 200ms
* La simulation **s'arrête automatiquement** dès que **chaque philosophe a mangé au moins 3 fois**

