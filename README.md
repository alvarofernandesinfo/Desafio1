# Desafio1
Primeiro desafio técnico Aditum

# FUNCIONAMENTO E UTILIZAÇÃO DO PROJETO:

- A finalidade do sistema é informar, de uma lista de restaurantes, quais estão abertos, dado um horário escolhido pelo usuário. O usuário escolhe um horário em uma caixa de edição informando a hora e o minuto e aperta o botão "OK".
- A lista de restaurantes abertos nesse horário aparecerá em um quadro logo abaixo.
- O sistema espera que exista um arquivo "csv" com os dados necessários para o sistema funcionar.

# ESCOLHAS:

- O arquivo enviado para o desafio foi um arquivo "xlsx". Foi utilizado um conversor online para convertê-lo para o formato "csv" requerido pelo sistema. 
- Foi escolhido um "timeEdit" para a entrada da hora por já ter fixado os limites dos valores de hora e minuto possíveis, facilitando a crítica da hora informada pelo usuário.
- O componente "listWidget" foi escolhido por facilitar a adição das strings linha a linha, relativas aos restaurantes selecionados.

# TESTES NECESSÁRIOS:

1) Teste da existência do arquivo de dados:
   - Renomear o arquivo para verificar o caso de erro de abertura do arquivo
   - Apagar o arquivo para verificar o caso de erro de abertura do arquivo
2) Teste de consistência de horário x restaurantes abertos
   - Testar com um horário que não retorne nenhum restaurante (escolher um horário que não esteja entre a hora de abertura e hora de fechamento de nenhum restaurante - Ex. 07:00)
   - Testar com um horário que retorne todos os restaurantes (escolher um horário que esteja entre a hora de abertura e fechamento de todos os restaurante. Ex 12:00). Conferir se realmente o número de restautantes retornados confere com o número de restaurantes na lista.
   - Testar com um horário que retorne um só restaurante (editar o arquivo "csv", escolher um restaurante qualquer e colocar o horário de fechamento maior do que qualquer outro restaurante e usar esse horário para consulta. Ex. 23:45)
   
   Obs: O sistema assume que o arquivo recebido não contém erros de consistência no formato ou nos dados fornecidos. Para simplificar o código não foi tratado, por exemplo, uma exceção para horários inconsistentes ou linhas com caracteres inválidos. Presume-se que o arquivo foi gerado de forma correta. Se necessário, essas críticas podem ser incluídas.
   
