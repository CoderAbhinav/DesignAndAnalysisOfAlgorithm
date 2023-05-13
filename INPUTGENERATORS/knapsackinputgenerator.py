import random

class Item:
    def __init__(self, weight, profit):
        self.weight = weight
        self.profit = profit

def generate_test_cases(num_items):
    items = []

    for _ in range(num_items):
        weight = random.randint(1, 100)
        profit = random.randint(1, 100)
        item = Item(weight, profit)
        items.append(item)

    return items

if __name__ == '__main__':
    # num_items = int(input("Enter the number of items: "))
    num_items = 20

    items = generate_test_cases(num_items)

    total_weight = sum(item.weight for item in items)
    sack_weight = total_weight // 2



    print(num_items)
    print(sack_weight)
    for i in items:
        print(f"{i.weight} {i.profit}")
