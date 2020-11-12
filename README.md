# blockchain
Second task for VU blockchain course

# How to use?

1. Open *main.cpp* and run it.

If you want to change the amount of users, transactions, just go to *header.h* where you can change constants of *USERAMOUNT*, *TRANSAMOUNT* to desired amount.

# V0.1 tasks : 

1. Generates a specific amount of users;

2. Generates a specific amount of transactions which are made with user ID's;

3. Stores 100 transactions in one block;

4. Program mines blocks until the amount of transactions left are more than 100; 

5. Finally, program outputs the hashes of blocks.

Mined block hash : 0fb642331cd411b0dc6c294120e50770650ab5d81aa2e5ab8780c084b353ab96

Mined block hash : 00a825f3c5310a1ee0be20590a28badbc4243ea429fac76329ea6fe0c30e0071

Mined block hash : 0a930bc404452cb5eadaa303cedb51510ab92ee5ca2304a60c092e883918f7a2

Mined block hash : 034a9c2e70fa2678c82528070027e0b080f1fa17198440a308de49b554a41766

Mined block hash : 094b298851e8cef248d7b07451ecce8780129b57e908c6b926ed863067117c89

Mined block hash : 0d4fe9159223396fe33061cd0b41cc45e0ccbedbba301aff6949291cb6835dcd

Mined block hash : 0f9b6f758fb96f8da30de54856c83845d431f4c527640820c3685dc45fdf6390

and so on...

# V0.2 tasks : 

Added merkle root hash function;

Added validation of transaction (if sender.amount > sender.balance -> transaction.erase)

Added validation of transaction ID.

*Five blocks candidates*


