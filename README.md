# Tickets:
- [X] Doubly linked list implementation for ticket.
- [X] Ticket first line should be one before metadata.
- [X] Ticket add_line to be added.
- [X] Parser for ticket metadata to be added

# Lines:
- [X] Parser for line numbers, time, and remarks (per line)
- [X] Handle adding Lines making sure no segfaults occur
- [ ] Have a way to query remarks.

# Database:
- [ ] Querying tickets should not be a strict match, but rather should have tolerance. For example, let's say metadata has 3 V, but a ticket is 3.2 V. Close enough, you should print that to the terminal.
- [ ] First, for the database it should be a class that contains a ticket list, the teams data(later on), and the occurences of people(Later on)
      Ex. class Database{
      Public:
      TicketList List;
      Hospital Teams;
      Occurences people;
      };
- [ ]  

# Direct-Future goals (In order of importance)
1. Printing tickets
2. Ticket Querying (filtering between dates, substation, incident type, and comment search). Note: This might mean we might have to re-think our header files, and implementation. Rather than having one giant function that does a massive query, we can divide-and-conquer for convenience
   - For this specfic point,(thinking specifically about the similar ticket task) I was thinking that we can iterate through our doubly linked list for each ticket, specfically looking at the comments, with each comment, we store every string in a binary tree which is organized based on string comparing (greater than or less than). THen we can use those trees to compare to other trees of ticket comments where we can see which trees are most similar to each other and store them in an array of similar ticket comments. When comaparing, every time that we find a ticket that is not similar to the previous we will begin comparing that ticket to other tickets, whilst still comparing the previous ticket. (if that makes sense.) Sort of like a bubble sort type of thing. 
4. AFTER WE IMPLEMENT THE ABOVE^^ We should get started with our report, to justify why our approach is good.

## Potential implementation ideas:
1. Operator overloading (for << ticket type)??
2. Trees (for database)??
3. To my teammate: Please add more ideas, I'm here to code, but management... is not really my thing (in case it hasn't been too obvious). My organizational skills are all over the place :P

# Far-Future goals:
- Write parser for Task 2
- Task 3 (Unknown plans as of now)
- Task 4 (Unknown plans as of now)
- Task 5 (Unknown plans as of now)
- Code optimization. We've just (barely) finished task 1, and our code is a disastrous mess in terms of optimization. Thankfully, it's memory safe.
