# ft\_ssl

### Table Of Contents
* [Objective](#objective)
* [Installation](#installation)
* [Usage](#usage)
* [Functions](#functions)
* [Future](#future)
* [Credits](#credits)

## Objective  
The goal of ft\_ssl is to build a collection of cryptography tools, replicating some of the behaviors of OpenSSL.

#### About 42  
[42][42] is a free, non profit, project-based, peer-to-peer learning coding school. It originated in France and now has over 20 campuses all over the world. More information can be found [here][42].

## Installation 
Clone this repository.
````
git clone https://github.com/pheilbron/ft_ssl.git
cd ft_ssl\
````
To create the archive, use
````
make && make clean
````

## Usage  
To use this library, include the appropriate header file in your programs.
When compiling with gcc, use the -L flag.
````
gcc [srcs] -L <libft path> -lft
````

## Future 
This library is updated from time to time as the needs of future 42 projects reveal themselves.

## Credits  
* README based on template by [Michael Brave](https://www.github.com/michaelbrave/)

[42]: http://42.us.org "School 42"
