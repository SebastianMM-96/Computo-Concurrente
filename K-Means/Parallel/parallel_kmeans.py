import csv, time, random, math
from mpi4py import MPI
import numpy
import matplotlib.pyplot as plt

'''
Funcion para obtener la distancia Euclidiana
'''
def dist_euclidiana(point_one, point_two):
	'''
		La asignacion de los datos en que cada punto de datos se asigna a un grupo 
		al centroide mas cercano segun la distancia euclidiana al cuadrado
	'''
	if(len(point_one) != len(point_two)):
		raise Exception("Error: los puntos no son comparables")

	sum_diff = 0.0
	for i in range(len(point_one)):
		diff = pow((float(point_one[i]) - float(point_two[i])), 2)
		sum_diff += diff
	final = math.sqrt(sum_diff)
	return final

def comparar_centroides(initial_center, derived_center, dimensions, num_clusters, cutoff):
	'''
		Paso de actualizacion de centroide tomando la media completa de 
		todos los puntos de datos asignados a ese grupo de centroides
	'''
	if(len(initial_center) != len(derived_center)):
		raise Exception("Error:los puntos no son comparables")

	flag = 0
	for i in range(num_clusters):
		diff = dist_euclidiana(initial_center[i], derived_center[i])
		if(diff < cutoff):
			flag += 1
	return flag


def main():
	# iniciamos la paralelizacion con MPI
	comm = MPI.COMM_WORLD # todos los procesos comparten un comunicador global
	rank = comm.Get_rank() # rank del comunicador
	size = comm.Get_size() # tamanio del comunicador

	global cutoff, dimensions, num_clusters, data, initial, min_dist
	cutoff = 0.2
	compare_val = 0
	
	with open('video_game_sales.csv','r') as f:
			reader = csv.reader(f)
			data = list(reader)
	data.pop(0)
	num_points = len(data)
	dimensions = len(data[0])
	initial = []
	for i in range(size):
		initial.append(data[i])
	# medimos el tiempo
	start_time = time.time()
	

	# la condicion de aqui permitira 
	# ejecutar hasta que todos los puntos de datos del archivo no cambien los 
	# clusteres definidos

	while True:	
		#print("Puntos iniciales: ", initial)
		dist = []
		min_dist = numpy.zeros(num_points)
		for point in data:
			dist.append(dist_euclidiana(initial[rank], point))

		temp_dist = numpy.array(dist)
		'''
			Toma la matriz de datos de entrada y las salidas al proceso root 
			con la operacion de reduccion 
			como valor minimo de la matriz de elementos
		''' 
		comm.Reduce(temp_dist, min_dist, op = MPI.MIN) # (las salidas contienen el elemento reducido) 
		# Bloqueamos los procesos hasta que alcancen al root.
		comm.Barrier()
		if rank == 0:
			min_dist = min_dist.tolist()
		# Operacion demasiada costosa
		# copia los datos del proceso root a todos en el comunicador
		recv_min_dist = comm.bcast(min_dist, root = 0)
		# bloqueamos hasta que todos hayan echo la copia de los datos
		comm.Barrier()
		cluster = []
		for i in range(len(recv_min_dist)):
			if recv_min_dist[i] == dist[i]:
				cluster.append(data[i])
		center = []
		center_val = [0] * dimensions
		for i in cluster:
			for j in range(dimensions):
				center_val[j] += float(i[j])

		for j in range(dimensions):
			if(len(cluster) != 0):
				center_val[j] = center_val[j] / len(cluster)

		# Recopilar todos los datos con un gather
		# mandarlos al proceso root
		center = comm.gather(center_val, root = 0)
		# bloqueamos hasta que todos recopilen los datos
		# para el proceso raiz
		comm.Barrier()
		if rank == 0:
		 	compare_val = comparar_centroides(initial, center, dimensions, size, cutoff)
		 	if compare_val == size:
		 		print ("Final centers are: ")
		 		print(center)
		 		print ("Execution time %s seconds" % (time.time() - start_time))
		
		break_val = comm.bcast(compare_val, root = 0)

		initial = comm.bcast(center, root = 0)
		comm.Barrier()

		if break_val == size:
			break

if __name__ == "__main__":
	main()