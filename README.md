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

# Direct-Future goals (In order of importance)
1. Printing tickets
2. Ticket Querying (filtering between dates, substation, incident type, and comment search). Note: This might mean we might have to re-think our header files, and implementation. Rather than having one giant function that does a massive query, we can divide-and-conquer for convenience
3. AFTER WE IMPLEMENT THE ABOVE^^ We should get started with our report, to justify why our approach is good.

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
