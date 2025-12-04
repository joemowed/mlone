import numpy as np
test_data = ((0,0,1),(0,1,1),(1,0,1),(1,1,0))
def init_weights(mat:np.ndarray):
    #xavier initialization
    sigma = np.sqrt(6/(mat.shape[1]+mat.shape[0]))
    
    for index_tuple in np.ndindex(mat.shape):
        mat[index_tuple] = np.random.normal(loc=0,scale=sigma)

INPUT_SIZE = 2;
H1_SIZE = 4;
Y_SIZE =2;

weights_h1 = np.zeros((H1_SIZE,INPUT_SIZE))
weights_y = np.zeros((Y_SIZE,H1_SIZE))
print(weights_h1.shape)
print(weights_y.shape)
init_weights(weights_h1)
init_weights(weights_y)
    
