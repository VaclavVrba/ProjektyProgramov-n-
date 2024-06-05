
function addRow(){
    let table = document.getElementById("basicInfo");
    let taskInput = document.getElementById("task");
    let task = taskInput.value;

    let deleteButton = document.createElement('button');
    let row = document.createElement('tr');
    let cell = document.createElement('td');
    let cell2 = document.createElement('td');

    deleteButton.textContent = 'DELETE';
    deleteButton.name='PleaseMakeMeRed';
    deleteButton.onclick = function(){
        table.deleteRow(row.rowIndex);
    };
    
    cell.textContent = task;
    cell.classList.add('PleaseMoveMeLeft');
    cell2.appendChild(deleteButton);

    row.appendChild(cell);
    row.appendChild(cell2);
    table.appendChild(row);

    taskInput.value = '';
}