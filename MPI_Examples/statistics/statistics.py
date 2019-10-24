from mpi4py import MPI
from random import randint
import sys
import math
from quick_select import partition, kthlargest


def findMean(val_):
	comm = MPI.COMM_WORLD

	sum = 0
	for i in range(len(val_)):
		sum += val_[i]
	mean = float(sum / len(val_))
	print("Mean Value is: ", mean)

	# send the result 
	comm.send(mean, dest = 1, tag = 1)

def findMedian(val_):
	# get the communicator
	comm = MPI.COMM_WORLD

	max_min = comm.recv(source = 2, tag = 2)

	if len(val_) % 2 == 0:
		aux_ = len(val_) / 2
		res_1 = kthlargest(val_, aux_)
		res_2 = kthlargest(val_, aux_ + 1)

		glb_res = (res_1 + res_2) / 2
	else:
		aux_ = (len(val_) / 2) + 1
		glb_res = kthlargest(val_, aux_)

	print("Median Value is: ", glb_res)

def find_max_min(val_):
	max_min = [val_[0], val_[0]]
	for x in range(1, len(val_)):
		if max_min[0] < val_[x]:
			max_min[0] = val_[x]
		if max_min[1] > val_[x]:
			max_min[1] = val_[x]
	print("Max & Min is: ", max_min)

	# send the result 
	comm.send(max_min, dest = 3, tag = 2)

# Standar deviation
def standardDeviation(val_):
	comm = MPI.COMM_WORLD

	mean = comm.recv(source = 0, tag = 1)

	deviation = 0
	for x in range(len(val_)):
		deviation = ((val_[x] - mean)**2) + deviation

	# get the standar deviation
	desvst = math.sqrt((deviation / len(val_) - 1))

	print("Standar Deviation value: ", desvst)


def main():
	# get the communicator
	comm = MPI.COMM_WORLD
	rank = comm.Get_rank()
	size = comm.Get_size()

	# all to root process
	if rank == 0:
		Array = []

		# get from user to calculate 
		getN = int(sys.argv[1])

		for x in range(0, getN):
			# filled with random numbers
			Array.append(randint(0, 10))
	else:

		Array = None
	# send array to all nodes
	Array = comm.bcast(Array, root = 0)
	# root node do:
	if rank == 0:
		print("The Array is: ", Array)
		findMean(Array)

	elif rank == 1:
		standardDeviation(Array)
	elif rank == 2:
		find_max_min(Array)
	elif rank == 3:
		findMedian(Array)

if __name__ == '__main__':
	main()