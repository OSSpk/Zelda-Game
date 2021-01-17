# 👽 Zelda-Game

<a href="https://github.com/harismuneer"><img alt="views" title="Github views" src="https://komarev.com/ghpvc/?username=harismuneer&style=flat-square" width="125"/></a>

[![Open Source Love svg1](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](#)
[![GitHub Forks](https://img.shields.io/github/forks/harismuneer/Zelda-Game.svg?style=social&label=Fork&maxAge=2592000)](https://www.github.com/harismuneer/Zelda-Game/fork)
[![GitHub Issues](https://img.shields.io/github/issues/harismuneer/Zelda-Game.svg?style=flat&label=Issues&maxAge=2592000)](https://www.github.com/harismuneer/Zelda-Game/issues)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat&label=Contributions&colorA=red&colorB=black	)](#)


A text based game made as a final project for the course "Computer Programing CS103" during my 2nd Semester at [National University of Computer and Emerging Sciences](http://nu.edu.pk/).

## How to Run
Just run Zelda.exe. If it doesnt work, then add the .txt files and the .cpp file in a new project (console application) in Microsoft Visual Studio and then build the project and run it.

## Game Description
*(This is purely a work of fiction and any resemblance to an actual person or monster is purely coincidental.)*

The princess of the kingdom of CPeria has been captured by an evil wizard and placed in a castle guarded by monsters. Your job is to set her free and bring her back outside the castle. The castle has 9 rooms. The game starts with you standing in room 1. Room 1 had the exit to the castle on its west. Some of the rooms are linked together. Each room had either a wall on its north, south, east or west or another room (see maze below).  The princess is locked in room 9. There are two monsters in the castle that need to be killed in order to reach the princess. Each monster is guarding a magical path and whenever you kill a monster, this path appears and two rooms get linked together. Fortunately, the monsters are rather docile and do not attack you unless you attack them. 

The first monster that you need to kill is the snake headed lady from Greek myth affectionately called Medusa by some. She is so beautiful that whenever someone sees her, he or she turns to stone. The trick to kill her is to attack her using a magic shield. This shield can be picked up from room 3. Medusa will see her own reflection in the shield and turn to stone. As soon as she dies, a pathway will appear which will let you explore room 7 and 8.

The second monster is Mr. Dracula. To finish him off, you must attack him using a silver dagger right through his heart. You can find the dagger in room 7 while Dracula is in room 6. He guards a door which opens up in room 9 when he is killed. On killing him, you have to get to the princess and must lead her out to the exit once you do that. 

There are treasure-items scattered throughout the castle for the financially inclined ones. Since you carry a bag with you, you can put all the items that you pick during the game (the treasure, the dagger and the magical shield) in that bag. The bag can only contain at the most 10 items at a time. The treasure is of three types. There is a golden egg in room 2 and a golden chalice in room 4. In room 8, there’s a piece of paper with the proof of the famous unsolved problem P=NP on it . The golden egg and the golden chalice are worth half a million dollar each; where as the proof paper is worth a million dollar. Unfortunately there are no buyers of the shield and dagger so they are of no particular value in the OOPtopia black market. 

Once an item is picked, you can drop it in any room if you want. If a monster is attacked without the weapon that he can be killed with in your bag, you’ll die. If you get out of the castle without freeing the princess, you’ll lose the game.

![](../master/images/i.png)

## Interface
![interface](../master/images/interface.png)

## Project Requirements
Your project is to implement this game. Here are a few requirements that need to be implemented. 

*	The game should start by stating the story in two or three lines. This story should be present in a file called Start.txt.
*	The user should input all moves as text commands. Valid commands are MOVE, PICK, DROP, EXIT, ATTACK, LOOK
*	The MOVE command should take the direction in which the user wants to move as the second parameter. The directions can be NORTH, SOUTH, EAST or WEST. For example, on entering the MOVE EAST command in room 1, the user should move to the room 2. 
*	If there is a wall on the side, a message should be displayed telling the user that the move is not possible. For example, MOVE EAST is an invalid command. 
*	Whenever the user moves to the new room, a one line description of the room should be displayed. The description of all the rooms should be present in a file called Rooms.txt which should be read at the beginning of the program and stored in memory. 
*	After the room description, all the possible exits from the room should be displayed. 
*	If there are any items in the room, they should be displayed after the exit path list. There cannot be more than 5 items in a room.
*	If there is a monster in the room, its name should be displayed after the item list. A room can contain at the most one monster. e.g. if a user enters a room with a door to east and west, the dagger and Medusa (alive), the description will be. 

*This room has weird shapes drawn all over the walls and flickering torches make the faces even scarier. There is a door to your east. There is a door to you west. The dagger is lying on the floor. Medusa is waiting to kill you beside a locked door.*

*	The PICK command should accept the object to be picked as the second parameter. e.g. In the above example, if the user type the command PICK DAGGER, it should remove the dagger from the room, add the dagger to the user’s bag and display a message on the screen. Something that is not in the room should not be allowed to be picked. 
*	The DROP command should also accept the object to be dropped from the user’s bag into the current room.
*	The EXIT command should exit the program.
*	The ATTACK command should attack the monster in the room (if there is one). If the weapon that the monster can be killed with is in the bag, the monster should die. Other wise it should kill the user. In case of a death by the hands of monster, the game should end after displaying all the text in a file called EndDead.txt on the screen.
*	A monster’s death should create a link between two rooms and its body should remain on the floor. Medusa is guarding the link between room 5 and room 8. Dracula is guarding the link between room 6 and room 9.
*	The LOOK command should print out the description of the room including all the items and doors in the room.
*	If the user exits the castle after rescuing the princess, the text in a file called EndWin.txt should be displayed and the game should end. 
*	If the user exits the castle without rescuing the princess, the text in a file called EndLose.txt should be displayed and the game should end. 

<hr>

<h1 align="left">Hey there, I'm <a href="https://www.linkedin.com/in/harismuneer/">Haris </a><img src="https://media.giphy.com/media/hvRJCLFzcasrR4ia7z/giphy.gif" width="28"> 
 <a href="https://github.com/harismuneer/Ultimate-Facebook-Scraper"><img align="right" src="https://user-images.githubusercontent.com/30947706/79588950-17515780-80ee-11ea-8f66-e26da49fa052.png" alt="Ultimate Facebook Scraper (UFS)" width="200"/></a> - Maker of Things</h1> 


### Creator of <a href="https://github.com/harismuneer/Ultimate-Facebook-Scraper">Ultimate Facebook Scraper</a> (one of the best software to collect Facebook data for research & analysis) 

<hr>

<h2 align="left">🌐 Connect</h2>
<p align="left">
  <a href="https://www.linkedin.com/in/harismuneer/"><img title="Follow on LinkedIn" src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"/></a>
  <a href="https://www.facebook.com/harism99"><img title="Connect on Facebook" src="https://img.shields.io/badge/Facebook-1877F2?style=for-the-badge&logo=facebook&logoColor=white"/></a>
  <a href="https://twitter.com/harismuneer99"><img title="Follow on Twitter" src="https://img.shields.io/badge/Twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white"/></a>
  <a href="mailto:haris.muneer5@gmail.com"><img title="Email" src="https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white"/></a>
  <a href="https://github.com/harismuneer"><img title="Follow on GitHub" src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white"/></a>
  <a href="https://www.instagram.com/harismuneer99"><img title="Follow on Instagram" src="https://img.shields.io/badge/Instagram-E4405F?style=for-the-badge&logo=instagram&logoColor=white"/></a>
  <a href="https://www.youtube.com/channel/UCZ-uBd7g0E2Bp-0tXtSlSjw?sub_confirmation=1"><img title="Subscribe on YouTube" src="https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=youtube&logoColor=white"/></a>
</p>


## 🤝 Consulting / Coaching
Stuck with some problem? Need help in solution development, guidance, training or capacity building? I am a Full Stack Engineer turned Project Manager with years of technical and leadership experience in a diverse range of technologies and domains. Let me know what problem you are facing at <b>haris.muneer5@gmail.com</b> and we can schedule a consultation meeting to help you get through it.

## 👨‍💻 Technical Skills & Expertise

- Development of Web Applications, Mobile Applications, and Desktop Applications
- Development of Machine Learning/Deep Learning models, and deployment 
- Web Scraping, Browser Automation, Python Scripting
<hr>


## ❤️ Support / Donations
If you or your company use any of my projects, like what I’m doing or have benefited from my projects in any way then kindly consider backing my efforts.

For donations, you can follow these simple steps:

<b>1)</b> Free signup at <b>[TransferWise](https://transferwise.com/invite/u/harism95)</b> using this link: https://transferwise.com/invite/u/harism95</li>. (Signing up through this link will save you from any transcation fee on the donation)

<b>2)</b> Select the amount e.g (15$) and choose the receiving/recipient's currency to be PKR. It supports multiple payment options (credit card, debit card, wire transfer etc)

<b>3)</b> Then it will show my info as the recipient, select it. If my name isn't shown, then type my email haris.muneer5@gmail.com in recipients.

<b>4)</b> Choose the reason for transfer to the one that suits you the most (in this case it could be 'General expenses') and in the reference section, you can mention 'Support'
 
If you face any issue in sending donation then feel free to get in touch with me at haris.muneer5@gmail.com 

Thank you for your contribution!


## Author
You can get in touch with me on my LinkedIn Profile: [![LinkedIn Link](https://img.shields.io/badge/Connect-harismuneer-blue.svg?logo=linkedin&longCache=true&style=social&label=Follow)](https://www.linkedin.com/in/harismuneer)

You can also follow my GitHub Profile to stay updated about my latest projects: [![GitHub Follow](https://img.shields.io/badge/Connect-harismuneer-blue.svg?logo=Github&longCache=true&style=social&label=Follow)](https://github.com/harismuneer)

If you liked the repo then kindly support it by giving it a star ⭐ and share in your circles so more people can benefit from the effort.


## Contributions Welcome
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](#)

If you find any bug in the code or have any improvements in mind then feel free to generate a pull request.

## Issues
[![GitHub Issues](https://img.shields.io/github/issues/harismuneer/Zelda-Game.svg?style=flat&label=Issues&maxAge=2592000)](https://www.github.com/harismuneer/Zelda-Game/issues)

If you face any issue, you can create a new issue in the Issues Tab and I will be glad to help you out.

## License
[![MIT](https://img.shields.io/cocoapods/l/AFNetworking.svg?style=style&label=License&maxAge=2592000)](../master/LICENSE)

Copyright (c) 2018-present, harismuneer                                                        
