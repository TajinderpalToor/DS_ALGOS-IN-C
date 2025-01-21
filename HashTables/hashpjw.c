/*
Chained Hash Tables:

- hash tables that store data in buckets, each bucket is a linked list
that can grow as needed to deal with collisions 

- if the table becomes to full, the performance degrades
because as the table grows, the number of collissions increases, more
elements hash to the same bucket

- so basically give a key, key goes to hash function ( hashing they key), to get what bucket to go to
then traverse the list to find which element your looking for 

Collision Resolution:

- when collision occurs elements are simply placed in the bucket where the collision occurs
- but the problem with this is that if alot of collisions occur at a specific place, that bucket keeps getting longer
and longer, so when you have to get to the element it takes long

- ideally seperate the elements uniformally so that the buckets are uniformally distributed
so that buckets dont get too large, even this can become a problem because if you have less buckets (in relation to the number of elements you want to add)
then the buckets can become large 

Hash Table Load Factor: x=n/m
-> n = number of elements in table
-> m = number of positions into which elements may be hashed ( buckets )

-> n/m the result will give the max number of elements you can expect in a bucket 
-> in practice the load factor is an approximation, depending on your hash function 
you can get it close enough to load factor 

Selecting a Hash Function:

x (position) is called the hash coding of k
h(k) = x

Division Method:

- map into one of the m positions in a table by taking k (key) divided by m (number of positions)
-h(k)= k mod m
- m is usually a prime number not too close to a power of 2

Multiplication Method:
- h(k) = floor( m(kA mod 1) ), where A in range 0<A<1 and A usually 0.618


hash table good for strings, pg 146-147

*/

