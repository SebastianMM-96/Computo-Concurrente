# Import from module mpi4py the object MPI
from mpi4py import MPI
import array
from sys import argv
import random

# Funcion para ganador
def analyze_sample(sample):
	count = 0
	for i in sample:
		if i == 1:
			count += 1
	return 1 if count > len(sample)//2 else 0

# Tarea que simula Ping_Pong
def ping_pong_task(rounds, sample):
	comm = MPI.COMM_WORLD
	rank = comm.rank
	n = 0
	partner = (rank+1)%2
	while n < rounds:
		num = array.array('i',[random.randrange(2)])
		if rank == (n%2):
			comm.Send([num, MPI.INT], partner, tag = n)
		else:
			partner_num = array.array('i',[0])
			comm.Recv([partner_num, MPI.INT], partner, tag = n)
			if num[0] > partner_num[0]:
				sample.append(rank)
			else:
				sample.append(partner)
		n += 1
	if rank == 0:
		sample_partner = array.array('i',[0]*len(sample))
		comm.Recv([sample_partner, MPI.INT], partner, 0)
		sample += sample_partner
	else:
		comm.Send([sample, MPI.INT], partner, 0)

# Funcion para iniciar una partida de ping pong.
def ping_pong(r):
	comm = MPI.COMM_WORLD
	p = comm.size
	assert(p == 2)
	sample = array.array('i',[])
	rounds = r
	ping_pong_task(rounds, sample)
	winner = analyze_sample(sample)
	return winner

# This is the main funcion, don't forget it
def main():
	rank = MPI.COMM_WORLD.rank
	r = int(argv[1])
	winner = ping_pong(r)
	if(rank == 0):
		print('The winner is the process ' + str(winner))

if __name__ == "__main__":
    main()