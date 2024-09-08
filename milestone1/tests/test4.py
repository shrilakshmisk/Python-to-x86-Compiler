tasks : list [str]= []  
completed_tasks  : list[str] = []  
task_id_counter : int = 1

def add_task(title : str, description : str) -> None:
    global task_id_counter
    task : str = title
    tasks.append(task)
    print("Task added: ", title)
    task_id_counter += 1

def complete_task(task_id : str) -> None:
    global completed_tasks
    task : str = ""
    for task in tasks:
        if task == task_id:
            tasks.remove(task)
            completed_tasks.append(task)
            print("Task completed ", task)
            return
    print("Task not found.")

def display_tasks() -> None:
    if not tasks:
        print("No active tasks.")
    else:
        print("Active tasks:")
        task : str = ""
        for task in tasks:
            print(task)

def display_completed_tasks() -> None:
    if not completed_tasks:
        print("No completed tasks.")
    else:
        print("Completed tasks:")
        task : str = ""
        for task in completed_tasks:
            print(task)


def main() :
    add_task("Buy groceries", "Milk, Eggs, Bread, Butter")
    add_task("Read a book", "Complete reading 'The Alchemist'")
    add_task("Exercise", "30 minutes of cardio")

    print("\nBefore completing any tasks:")
    display_tasks()

    complete_task("Exercise")

    print("\nAfter completing a task:")
    display_tasks()

    print("\nCompleted tasks:")
    display_completed_tasks()

if __name__ == "__main__":
    main()

