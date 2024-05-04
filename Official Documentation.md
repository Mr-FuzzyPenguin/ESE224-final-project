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

### Most Similar Tickets - 
For this question we assumed that we would be comparing this "similar tickets" relative to a ticket that an operator would already be looking at. And so in our function will pass the parameter Y as the number of similar tickets that we want to find, alongside another parameter which will contain the name of a file of a ticket that we want to compare to. And so this output of this function will output a Y number of similar tickets to ticket X. 

For the within the same substations, we will just put a restriction on the pool of data that this function will have access to compare to. And for the different substations will we do the same in order to not allow the tiicket to be compared to tickets withint the same substation. 

### Most Frequent Words - 
For this question we will pass two parameters, one being the substation, X, and they other people the K number of frequent words that we want to find. And so in this function we will go to all the tickets within a specific substation then we will pool all the comments together and could the most frequent words within the pool of comments. Then we will output each word and it's respective frequency.

# Question 2: 
## Hospital Database 
