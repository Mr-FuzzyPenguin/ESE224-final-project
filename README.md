# Question 1: 
## Ticket's Database 

### Overall-List

Start off with our Ticket List. This would be in the form of  a Doubly Linked List. This means that each ticket would have a pointer towards the next ticket and a pointer towards the previous ticket. We will manually go through each ticket when we need to go through it, using some type temp variable. 

### Each-Ticket
--
For each ticket it will contain the information from the first line. (includes the substation, the initial voltage, etc.) It will also contain a Doubly Linked list of lines as well to store the rest of the lines of the ticket.
### Each-Line
--
Each line will contain information regarding line number, time, remark, substation, etc. 
#### Add Line - addLine(string data)
This will update the ticket node of the ticket list, by adding a line node to the line list.
#### Ticket Display - //function
This will display the contents of our ticket. We will go through every single of ticket, by utilizing the doubly linked list of lines. 

### Outage Display by Period - 
For this specific question after looking at the ticket examples we realized that each substation can have multiple outages at different addresses. And so, with this in mind, since the goal is to show the amount of outages within a certain period of time. We will first output the amount of total outages within that period of time for a specific substation that was passed as a parameter to our function. Then we will display each ticket's first line of information that includes the time at which the ticket was created and the addressed in which the outage had occurred in.

#### Implementation - 
So the way that this code will be implemented is that for checking similar tickets within the same substation:
1. Take the substation from ticket X. And use that substation to parse through all the tickets within our database to find all the tickets for that substation, 
2. Simultaneously Store those tickets in a separate singly linked list. (or another data structure if preferred, Stanley)
3. Now we compare our ticket X to all the tickets within the single linked list of tickets within that specific substation. 
4. Each non-similar ticket will be deleted from this singly linked list until the similar tickets are left in which we will print them out in the output 
5. Delete this singly linked list afterwards (if not too difficult)
For different substation: 
6. Same steps in, but instead of storing the tickets with the same substation we will store the tickets that do not have the substation name on it. 
###### What is a similar Ticket?
As for the criteria for what constitutes tickets being similar would be the tickets having the same frequency of words with a 2-3 word frequency difference. (Making this the criteria we can simultaneously create the frequency function within this implementation.)

1.  Map out the frequency of each word within ticket X (the parameter). 
2. For each ticket we will find the frequency of words then compare the top 3 most frequent words to that of ticket X.
3.  If they fall within a +/-2-3 word difference then we can say that these tickets are similar. 

Potentially something like if the word is not in the data base already that it will be added, but if it is in the database then we will increase the frequency number by 1. And so with this in mind I was thinking that we could create a class within itself that is solely dedicated to the frequency of the words. 

### Most Frequent Words - 
For this question we will pass two parameters, one being the substation, X, and they other people the K number of frequent words that we want to find. And so in this function we will go to all the tickets within a specific substation then we will pool all the comments together and could the most frequent words within the pool of comments. Then we will output each word and it's respective frequency.

# Question 2: 
## Hospital Database 
