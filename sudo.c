int i;

/*
초기 fd 세팅: in_fd = 0, out_fd = -1; // rdr infile 없으면 표준 입력을 읽을 거고, 있으면 infile로 교체 됨. outfile은 없으면 pipe fd[1], 있으면 outfile로 교체 됨
*/

i = -1;
read_fd = 0;
while (++i < PL 개수)
{
	ast->in_fd = read_fd;

	if (i + 1 == PL 개수) // 마지막 턴 이면
		out_fd = 1; // 마지막 out_fd를 표준 출력으로 바꿔줘야 fork 후 자식이 pipe fd[1]에 쓰지 않고 표준 출력에 쓸 수 있음. rdr 후 아웃파일 있으면 그 아웃파일에 쓰게 됨 
	rdr tree 순회(); // rdr 순회해서 infile/outfile 세팅 해줌
	read_fd = excute(); // 여기서 조건 검사 후 builtin(); excute_cmd();로 나뉘어서 실행
}
close(read_fd); // 파이프 마지막에 pipe fd[0]; 안닫았기 때문에 while문 종료 후 close
all_free(); // 관련 해제해야 할 거 다 풀고 read_line으로 복귀