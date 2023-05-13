import random

def generate_test_case(n):
    # Generate random coordinates for cities
    cities = [(random.randint(0, 100), random.randint(0, 100)) for _ in range(n)]
    
    # Generate adjacency matrix
    adjacency_matrix = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(i+1, n):
            distance = calculate_distance(cities[i], cities[j])
            adjacency_matrix[i][j] = distance
            adjacency_matrix[j][i] = distance
    
    return adjacency_matrix

def calculate_distance(city1, city2):
    x1, y1 = city1
    x2, y2 = city2
    return  int(((x2 - x1)**2 + (y2 - y1)**2) ** 0.5)

# Generate a test case with 5 cities
test_case = generate_test_case(5)
print(test_case)
