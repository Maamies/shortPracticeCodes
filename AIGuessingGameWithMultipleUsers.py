import random
import re

def compare_guesses(guesses):
    random_value = random.randint(1, 9)
    print(f"Random value: {random_value}")  # Print the random value for clarity
    
    # Calculate differences from the random value
    differences = [(name, abs(int(value) - random_value)) for name, value in guesses]
    min_diff = min(differences, key=lambda x: x[1])[1]
    
    # Find all guesses with the minimum difference
    closest_guesses = [name for name, diff in differences if diff == min_diff]
    closest_values = list(set([value for name, value in guesses if abs(int(value) - random_value) == min_diff]))

    if len(closest_guesses) > 1:
        print(f'The closest were {", ".join(closest_guesses)} with value/s {", ".join(closest_values)}. The right value was {random_value}')
    else:
        print(f'The closest was {closest_guesses[0]} with value {closest_values[0]}. The right value was {random_value}')

def format_guesses(guesses):
    formatted_guesses = []
    for guess in guesses:
        entries = guess.split(", ")
        for entry in entries:
            name, value = entry.split(": ")
            formatted_guesses.append((name, value))
    return formatted_guesses

def main():
    guess_pattern = re.compile(r'.*: [1-9]')
    guesses = []
    
    while True:
        guess = input("Enter a name and a guess from 1-9 in the form of 'name: number' or 'name: number, ...'. Press 'q' to stop adding: ")
        if guess.lower() == "q":
            break
        if guess_pattern.match(guess):
            guesses.append(guess)
        else:
            print("Please provide the correct format. Example: 'josh: 2'")
    
    if guesses:
        formatted_guesses = format_guesses(guesses)
        compare_guesses(formatted_guesses)

if __name__ == "__main__":
    main()
