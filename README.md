# ft_irc
## Compilation
This project uses only the standard libraries, so no additional dependencies are required. To compile the program, run
```
make
```

## Usage
Once compiled, the executable will be `ircserv`, Usage:
```
./ircserv <port> <password>
```

## Commands
The Mandatory commands are `PASS`, `NICK`, `USER`, `JOIN`, `PART`, `PRIVMSG`, `KICK`, `INVITE`, `TOPIC`, `MODE`.  
Server-to-server communication was intentionally not implemented, as required by the subject.

## Bonus
### About
The bonus asked by the subject is a Bot. We implemented a bot that let you speak with ChatGPT.  
Since we didn't find a name for it, every time it starts, A name is asked to chatGPT and that will be the name used until stopped.  
The bot keeps track of every conversation with every user until stopped, ChatGPT will have the context of previous messages.  

The HTTP requests implementation is very basic and does not support HTTPS. To make requests to OpenAI, you will need a unsecured server that forwards your HTTP requests.

### compilation
To compile the bot, run: 
```
make bonus
```

### usage
once compiled, the executable will be named `bot`. Usage: 
```
./bot <ip> <port> <pass>
```
