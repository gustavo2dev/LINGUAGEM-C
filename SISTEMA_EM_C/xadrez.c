#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// Códigos das peças
#define EMPTY   0
#define WPAWN   1
#define WROOK   2
#define WKNIGHT 3
#define WBISHOP 4
#define WQUEEN  5
#define WKING   6
#define BPAWN  -1
#define BROOK  -2
#define BKNIGHT -3
#define BBISHOP -4
#define BQUEEN  -5
#define BKING  -6

// Cores ANSI
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BG_GRAY   "\033[100m"
#define BG_DARK   "\033[40m"
#define BG_YELLOW "\033[103m"

// Estruturas
typedef struct {
    int row, col;
} Position;

typedef struct {
    int fromRow, fromCol, toRow, toCol;
} Move;

// Tabuleiro global
int board[8][8];
int currentPlayer = 1; // 1 = brancas, -1 = pretas
bool inCheck = false;
bool gameOver = false;
char winner[10] = "";

// Posição dos reis (para xeque)
Position whiteKingPos, blackKingPos;

// Inicializa o tabuleiro
void initBoard() {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            board[r][c] = EMPTY;

    // Peões
    for (int c = 0; c < 8; c++) {
        board[1][c] = BPAWN;
        board[6][c] = WPAWN;
    }

    // Torres
    board[0][0] = BROOK; board[0][7] = BROOK;
    board[7][0] = WROOK; board[7][7] = WROOK;

    // Cavalos
    board[0][1] = BKNIGHT; board[0][6] = BKNIGHT;
    board[7][1] = WKNIGHT; board[7][6] = WKNIGHT;

    // Bispos
    board[0][2] = BBISHOP; board[0][5] = BBISHOP;
    board[7][2] = WBISHOP; board[7][5] = WBISHOP;

    // Rainhas
    board[0][3] = BQUEEN;
    board[7][3] = WQUEEN;

    // Reis
    board[0][4] = BKING; blackKingPos = (Position){0, 4};
    board[7][4] = WKING; whiteKingPos = (Position){7, 4};
}

// Converte notação "e2" para índices (row, col)
bool parsePosition(const char *s, int *row, int *col) {
    if (strlen(s) < 2) return false;
    char colChar = tolower(s[0]);
    char rowChar = s[1];
    if (colChar < 'a' || colChar > 'h' || rowChar < '1' || rowChar > '8') return false;
    *col = colChar - 'a';
    *row = 8 - (rowChar - '0');
    return true;
}

// Retorna caractere da peça
char pieceToChar(int p) {
    switch (abs(p)) {
        case WKING:   return 'K';
        case WQUEEN:  return 'Q';
        case WROOK:   return 'R';
        case WBISHOP: return 'B';
        case WKNIGHT: return 'N';
        case WPAWN:   return 'P';
        default:      return ' ';
    }
}

// Desenha o tabuleiro
void drawBoard() {
    system(CLEAR);
    printf("\n  ");
    for (char c = 'a'; c <= 'h'; c++) printf("  %c ", c);
    printf("\n");

    for (int r = 0; r < 8; r++) {
        printf("%d ", 8 - r);
        for (int c = 0; c < 8; c++) {
            int piece = board[r][c];
            bool isKingInCheck = false;
            if (piece == WKING && inCheck && currentPlayer == 1) isKingInCheck = true;
            if (piece == BKING && inCheck && currentPlayer == -1) isKingInCheck = true;

            // Fundo xadrez
            if ((r + c) % 2 == 0) printf(BG_GRAY); else printf(BG_DARK);

            // Se o rei estiver em xeque, fundo amarelo
            if (isKingInCheck) printf(BG_YELLOW);

            // Cor da peça
            if (piece > 0) printf(CYAN BOLD);   // brancas
            else if (piece < 0) printf(RED BOLD); // pretas

            char sym = pieceToChar(piece);
            printf(" %c ", sym);
            printf(RESET);
        }
        printf(" %d\n", 8 - r);
    }

    printf("  ");
    for (char c = 'a'; c <= 'h'; c++) printf("  %c ", c);
    printf("\n\n");
}

// Funções de geração de movimentos (similar à anterior, mas agora retornam vetor)
bool isInside(int r, int c) {
    return (r >= 0 && r < 8 && c >= 0 && c < 8);
}

// Adiciona movimento se a casa estiver vazia ou com peça adversária
void addMoveIfValid(int r, int c, int piece, Position moves[], int *count) {
    if (!isInside(r, c)) return;
    if (board[r][c] == EMPTY || board[r][c] * piece < 0)
        moves[(*count)++] = (Position){r, c};
}

// Movimentos do peão
void addPawnMoves(int r, int c, Position moves[], int *count) {
    int piece = board[r][c];
    int dir = (piece > 0) ? -1 : 1;
    int startRow = (piece > 0) ? 6 : 1;

    // Uma casa à frente
    int nr = r + dir;
    if (isInside(nr, c) && board[nr][c] == EMPTY) {
        moves[(*count)++] = (Position){nr, c};
        // Duas casas no primeiro movimento
        if (r == startRow) {
            int nnr = r + 2*dir;
            if (isInside(nnr, c) && board[nnr][c] == EMPTY && board[nr][c] == EMPTY)
                moves[(*count)++] = (Position){nnr, c};
        }
    }

    // Capturas diagonais
    for (int dc = -1; dc <= 1; dc += 2) {
        int capR = r + dir;
        int capC = c + dc;
        if (isInside(capR, capC) && board[capR][capC] != EMPTY &&
            board[capR][capC] * piece < 0)
            moves[(*count)++] = (Position){capR, capC};
    }
}

// Movimentos de deslizamento
void addSlidingMoves(int r, int c, int dirs[][2], int ndirs, Position moves[], int *count) {
    int piece = board[r][c];
    for (int d = 0; d < ndirs; d++) {
        int dr = dirs[d][0], dc = dirs[d][1];
        int nr = r + dr, nc = c + dc;
        while (isInside(nr, nc)) {
            if (board[nr][nc] == EMPTY) {
                moves[(*count)++] = (Position){nr, nc};
            } else {
                if (board[nr][nc] * piece < 0)
                    moves[(*count)++] = (Position){nr, nc};
                break;
            }
            nr += dr;
            nc += dc;
        }
    }
}

// Cavalo
void addKnightMoves(int r, int c, Position moves[], int *count) {
    int piece = board[r][c];
    int offsets[8][2] = {{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};
    for (int i = 0; i < 8; i++) {
        int nr = r + offsets[i][0];
        int nc = c + offsets[i][1];
        addMoveIfValid(nr, nc, piece, moves, count);
    }
}

// Rei (sem roque por enquanto)
void addKingMoves(int r, int c, Position moves[], int *count) {
    int piece = board[r][c];
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int nr = r + dr;
            int nc = c + dc;
            addMoveIfValid(nr, nc, piece, moves, count);
        }
    }
    // TODO: roque
}

// Gera todos os movimentos possíveis para a peça em (r,c) (sem considerar xeque)
int generatePseudoMoves(int r, int c, Position moves[]) {
    int count = 0;
    int piece = board[r][c];
    if (piece == EMPTY) return 0;

    int type = abs(piece);
    switch (type) {
        case WPAWN:   addPawnMoves(r, c, moves, &count); break;
        case WROOK: {
            int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
            addSlidingMoves(r, c, dirs, 4, moves, &count);
            break;
        }
        case WKNIGHT: addKnightMoves(r, c, moves, &count); break;
        case WBISHOP: {
            int dirs[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};
            addSlidingMoves(r, c, dirs, 4, moves, &count);
            break;
        }
        case WQUEEN: {
            int dirs[8][2] = {{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1}};
            addSlidingMoves(r, c, dirs, 8, moves, &count);
            break;
        }
        case WKING:   addKingMoves(r, c, moves, &count); break;
    }
    return count;
}

// Verifica se uma casa está sendo atacada por peças do jogador oponente
bool isSquareAttacked(int row, int col, int attackerColor) {
    // attackerColor: 1 = brancas, -1 = pretas
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            int piece = board[r][c];
            if (piece == EMPTY || piece * attackerColor <= 0) continue; // só peças do atacante
            Position moves[64];
            int count = generatePseudoMoves(r, c, moves);
            for (int i = 0; i < count; i++) {
                if (moves[i].row == row && moves[i].col == col)
                    return true;
            }
        }
    }
    return false;
}

// Verifica se o rei do jogador atual está em xeque
bool isKingInCheck(int player) {
    Position kingPos = (player == 1) ? whiteKingPos : blackKingPos;
    return isSquareAttacked(kingPos.row, kingPos.col, -player);
}

// Executa um movimento no tabuleiro (sem verificar xeque)
void applyMove(int fr, int fc, int tr, int tc) {
    int piece = board[fr][fc];
    board[tr][tc] = piece;
    board[fr][fc] = EMPTY;

    // Atualiza posição do rei se necessário
    if (abs(piece) == WKING) {
        if (piece > 0) whiteKingPos = (Position){tr, tc};
        else blackKingPos = (Position){tr, tc};
    }

    // Promoção de peão (automática para rainha)
    if (abs(piece) == WPAWN) {
        if ((piece > 0 && tr == 0) || (piece < 0 && tr == 7)) {
            // Promove para rainha (pode ser expandido depois)
            board[tr][tc] = (piece > 0) ? WQUEEN : BQUEEN;
        }
    }
}

// Desfaz um movimento (para validação)
void undoMove(int fr, int fc, int tr, int tc, int capturedPiece, int oldPiece) {
    board[fr][fc] = oldPiece;
    board[tr][tc] = capturedPiece;

    if (abs(oldPiece) == WKING) {
        if (oldPiece > 0) whiteKingPos = (Position){fr, fc};
        else blackKingPos = (Position){fr, fc};
    }
}

// Verifica se um movimento é válido (não deixa o próprio rei em xeque)
bool isMoveLegal(int fr, int fc, int tr, int tc) {
    int piece = board[fr][fc];
    int captured = board[tr][tc];
    int oldPiece = piece;

    // Executa o movimento
    applyMove(fr, fc, tr, tc);

    // Verifica se o rei do jogador que moveu ficou em xeque
    bool inCheckAfter = isKingInCheck(currentPlayer);

    // Desfaz o movimento
    undoMove(fr, fc, tr, tc, captured, oldPiece);

    return !inCheckAfter;
}

// Retorna true se o jogador atual não tem nenhum movimento legal
bool hasNoLegalMoves() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            int piece = board[r][c];
            if (piece == EMPTY || piece * currentPlayer <= 0) continue;

            Position moves[64];
            int count = generatePseudoMoves(r, c, moves);
            for (int i = 0; i < count; i++) {
                int tr = moves[i].row, tc = moves[i].col;
                if (isMoveLegal(r, c, tr, tc))
                    return false; // encontrou pelo menos um movimento legal
            }
        }
    }
    return true;
}

// Processa um movimento dado pelo usuário
bool processMove(const char *from, const char *to) {
    int fr, fc, tr, tc;
    if (!parsePosition(from, &fr, &fc) || !parsePosition(to, &tr, &tc)) {
        printf("Coordenadas inválidas.\n");
        return false;
    }

    int piece = board[fr][fc];
    if (piece == EMPTY) {
        printf("Não há peça na origem.\n");
        return false;
    }
    if (piece * currentPlayer <= 0) {
        printf("Essa peça não é sua.\n");
        return false;
    }

    Position moves[64];
    int count = generatePseudoMoves(fr, fc, moves);
    bool moveFound = false;
    for (int i = 0; i < count; i++) {
        if (moves[i].row == tr && moves[i].col == tc) {
            moveFound = true;
            break;
        }
    }
    if (!moveFound) {
        printf("Movimento inválido para esta peça.\n");
        return false;
    }

    if (!isMoveLegal(fr, fc, tr, tc)) {
        printf("Este movimento deixaria seu rei em xeque.\n");
        return false;
    }

    // Executa o movimento definitivamente
    int captured = board[tr][tc];
    applyMove(fr, fc, tr, tc);

    // Verifica xeque, xeque-mate ou afogamento
    currentPlayer = -currentPlayer; // muda para verificar o oponente
    inCheck = isKingInCheck(currentPlayer);

    if (hasNoLegalMoves()) {
        if (inCheck) {
            strcpy(winner, (currentPlayer == 1) ? "Pretas" : "Brancas");
            gameOver = true;
        } else {
            strcpy(winner, "Empate (afogamento)");
            gameOver = true;
        }
    }

    return true;
}

int main() {
    initBoard();
    char input[100];
    inCheck = false;

    while (!gameOver) {
        drawBoard();

        if (inCheck) {
            printf(BOLD YELLOW "XEQUE! " RESET);
        }
        printf("Vez das %s.\n", (currentPlayer == 1) ? "brancas" : "pretas");
        printf("Digite o movimento (ex: e2 e4) ou 'sair' / 'roque' / 'desistir': ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "sair") == 0 || strcmp(input, "desistir") == 0) {
            strcpy(winner, (currentPlayer == 1) ? "Pretas" : "Brancas");
            gameOver = true;
            break;
        }

        // Comando simples para roque (apenas didático, não verifica todas as regras)
        if (strcmp(input, "roque") == 0) {
            // Implementação básica de roque (apenas para teste)
            int kingRow = (currentPlayer == 1) ? 7 : 0;
            if (board[kingRow][4] == (currentPlayer == 1 ? WKING : BKING)) {
                // Tenta roque curto
                if (board[kingRow][5] == EMPTY && board[kingRow][6] == EMPTY &&
                    !isSquareAttacked(kingRow, 4, -currentPlayer) &&
                    !isSquareAttacked(kingRow, 5, -currentPlayer) &&
                    !isSquareAttacked(kingRow, 6, -currentPlayer) &&
                    board[kingRow][7] == (currentPlayer == 1 ? WROOK : BROOK)) {
                    applyMove(kingRow, 4, kingRow, 6);
                    applyMove(kingRow, 7, kingRow, 5);
                    currentPlayer = -currentPlayer;
                    inCheck = isKingInCheck(currentPlayer);
                    continue;
                }
            }
            printf("Roque não disponível.\n");
            continue;
        }

        char from[10], to[10];
        if (sscanf(input, "%s %s", from, to) != 2) {
            printf("Formato inválido. Use 'e2 e4'.\n");
            continue;
        }

        processMove(from, to);
    }

    drawBoard();
    printf("Fim de jogo! %s venceu.\n", winner);
    return 0;
}