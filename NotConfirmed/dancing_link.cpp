Public Class clsSudokuDLXBySudoku 
    Implements I_Sudoku 

    Private _Dance As clsDancingLinksSudoku 

    Private _Num(80) As Integer 

    Public Sub New() 
        Init() 
    End Sub 

    Public Function SetLine(Row As Integer, ParamArray Value() As Integer) As Boolean Implements I_Sudoku.SetLine 
        Dim I As Integer 
        For I = 0 To IIf(Value.Length < 10, Value.Length - 1, 8) 
            _Num(Row * 9 - 9 + I) = Value(I) 
        Next 
        Return True 
    End Function 

    Public Function Calculate() As String Implements I_Sudoku.Calculate 
        Dim I As Integer, J As Integer 
        Dim X As Integer, Y As Integer 
        Dim Index As New List(Of Integer), Value As New List(Of Integer) 
        Dim C1 As Integer, C2 As Integer, C3 As Integer, C4 As Integer 
        For I = 0 To 80 
            X = Int(I / 9) 
            Y = I Mod 9 
            If _Num(I) > 0 Then 
                C1 = X * 9 + Y + 1 
                C2 = X * 9 + _Num(I) + 81 
                C3 = Y * 9 + _Num(I) + 162 
                C4 = (Int(X / 3) * 3 + Int(Y / 3)) * 9 + _Num(I) + 243 
                _Dance.AppendLineByIndex(C1, C2, C3, C4) 
                Index.Add(I) 
                Value.Add(_Num(I))  
            End If 
        Next 

        _Dance.CompleteInsertMustSelectRow() 

        For I = 0 To 80 
            X = Int(I / 9) 
            Y = I Mod 9 
            If _Num(I) = 0 Then 
                C1 = X * 9 + Y + 1 
                C2 = X * 9 + 1 + 81 
                C3 = Y * 9 + 1 + 162 
                C4 = (Int(X / 3) * 3 + Int(Y / 3)) * 9 + 1 + 243 
                If _Dance.AppendLineByIndex(C1, C2, C3, C4) = True Then 
                    Index.Add(I) 
                    Value.Add(1) 
                End If 

                For J = 2 To 9 
                    If _Dance.AppendLineByIndex(C1, C2 + J - 1, C3 + J - 1, C4 + J - 1) = True Then 
                        Index.Add(I) 
                        Value.Add(J) 
                    End If 
                Next 
            End If 
        Next 

        Dim P() As Integer = _Dance.Dance 

        For I = 0 To 80 
            _Num(Index.Item(P(I) - 1)) = Value.Item(P(I) - 1) 
        Next 

        Dim V As String = "" 
        For I = 0 To 80 
            V = V & _Num(I) & "  " 
            If I Mod 9 = 8 Then V &= vbNewLine 
        Next 
        Return V 

    End Function 

    Public Sub Init() Implements I_Sudoku.Init 
        _Dance = New clsDancingLinksSudoku(324) 
        Dim I As Integer 
        For I = 0 To 80 
            _Num(I) = 0 
        Next 
    End Sub 
End Class 

Public Class clsDancingLinksSudoku 
    Private Left() As Integer, Right() As Integer, Up() As Integer, Down() As Integer 
    Private Row() As Integer, Col() As Integer 

    Private _Head As Integer 

    Private _Rows As Integer, _Cols As Integer, _NodeCount As Integer 
    Private Count() As Integer 

    Private Ans() As Integer 

    Private _HadInsertMustSelectRow As Integer 

    Public Sub New(ByVal Cols As Integer) 
        ReDim Left(Cols), Right(Cols), Up(Cols), Down(Cols), Row(Cols), Col(Cols), Ans(Cols) 
        ReDim Count(Cols) 
        Dim I As Integer 

        Up(0) = 0 
        Down(0) = 0 
        Right(0) = 1 
        Left(0) = Cols 

        For I = 1 To Cols 
            Up(I) = I 
            Down(I) = I 
            Left(I) = I - 1 
            Right(I) = I + 1 
            Col(I) = I 
            Row(I) = 0 

            Count(I) = 0 
        Next 

        Right(Cols) = 0 

        _Rows = 0 
        _Cols = Cols 
        _NodeCount = Cols 
        _Head = 0 

        _HadInsertMustSelectRow = 0 
    End Sub 

    Public Function AppendLine(ByVal ParamArray Value() As Integer) As Boolean 
        Dim V As New List(Of Integer) 

        Dim I As Integer 
        For I = 0 To Value.Length - 1 
            If Value(I) = 1 Then V.Add(I + 1) 
        Next 

        Return AppendLineByIndex(V.ToArray) 
    End Function 

    Public Function AppendLineByIndex(ByVal ParamArray Index() As Integer) As Boolean 
        Dim I As Integer, K As Integer = 0 

        If _HadInsertMustSelectRow > 0 Then 
            If Index.Length = 0 Then 
                _Rows += 1 
                Return True 
            Else 
                For I = 0 To Index.Length - 1 
                    If Count(Index(I)) = -1 Then Return False 
                Next 
            End If 
        Else 
            If Index.Length = 0 Then Return False 
        End If 

        _Rows += 1 

        ReDim Preserve Left(_NodeCount + Index.Length) 
        ReDim Preserve Right(_NodeCount + Index.Length) 
        ReDim Preserve Up(_NodeCount + Index.Length) 
        ReDim Preserve Down(_NodeCount + Index.Length) 
        ReDim Preserve Row(_NodeCount + Index.Length) 
        ReDim Preserve Col(_NodeCount + Index.Length) 
        ReDim Preserve Ans(_NodeCount + Index.Length) 

        For I = 0 To Index.Length - 1 

            _NodeCount += 1 

            If I = 0 Then 
                Left(_NodeCount) = _NodeCount 
                Right(_NodeCount) = _NodeCount 
            Else 
                Left(_NodeCount) = _NodeCount - 1 
                Right(_NodeCount) = Right(_NodeCount - 1) 
                Left(Right(_NodeCount - 1)) = _NodeCount 
                Right(_NodeCount - 1) = _NodeCount 
            End If 

            Down(_NodeCount) = Index(I) 
            Up(_NodeCount) = Up(Index(I)) 
            Down(Up(Index(I))) = _NodeCount 
            Up(Index(I)) = _NodeCount 

            Row(_NodeCount) = _Rows 
            Col(_NodeCount) = Index(I) 

            If _HadInsertMustSelectRow > 0 Then 
                Count(Index(I)) += 1 
            Else 
                Count(Index(I)) = -1 
            End If 
        Next 

        Return True 
    End Function 

    Public Sub CompleteInsertMustSelectRow() 
        Dim I As Integer 

        For I = 1 To _Cols 
            If Count(I) = -1 Then 
                Left(Right(I)) = Left(I) 
                Right(Left(I)) = Right(I) 
            End If 
        Next 

        For I = 1 To _Rows 
            Ans(I - 1) = I 
        Next 

        _HadInsertMustSelectRow = _Rows 
    End Sub 

    Public Function Dance() As Integer() 
        Return IIf(Dance(_HadInsertMustSelectRow) = True, Ans, Nothing) 
    End Function 

    Private Function Dance(ByVal K As Integer) As Boolean 

        If (Right(_Head) = _Head) Then 
            ReDim Preserve Ans(K - 1) 
            Return True 
        End If 

        Dim P As Integer, C1 As Integer 
        P = Right(_Head) 
        C1 = P 
        Do While P <> _Head 
            If Count(P) < Count(C1) Then C1 = P 
            P = Right(P) 
        Loop 

        If Count(C1) < 1 Then Return False 

        RemoveCol(C1) 

        Dim I As Integer, J As Integer 

        I = Down(C1) 
        Do While I <> C1 
            Ans(K) = Row(I) 

            J = Right(I) 
            Do While J <> I 
                RemoveCol(Col(J)) 
                J = Right(J) 
            Loop 

            If Dance(K + 1) Then Return True 

            J = Left(I) 
            Do While J <> I 
                ResumeCol(Col(J)) 
                J = Left(J) 
            Loop 

            I = Down(I) 
        Loop 

        ResumeCol(C1) 
        Return False 
    End Function 

    Public Sub RemoveCol(ByVal ColIndex As Integer) 

        Left(Right(ColIndex)) = Left(ColIndex) 
        Right(Left(ColIndex)) = Right(ColIndex) 

        Dim I As Integer, J As Integer 

        I = Down(ColIndex) 
        Do While I <> ColIndex 
            J = Right(I) 
            Do While J <> I 
                Up(Down(J)) = Up(J) 
                Down(Up(J)) = Down(J) 

                Count(Col(J)) -= 1 

                J = Right(J) 
            Loop 

            I = Down(I) 
        Loop 

    End Sub 

    Public Sub ResumeCol(ByVal ColIndex As Integer) 

        Left(Right(ColIndex)) = ColIndex 
        Right(Left(ColIndex)) = ColIndex 

        Dim I As Integer, J As Integer 

        I = Up(ColIndex) 

        Do While (I <> ColIndex) 
            J = Right(I) 
            Do While J <> I 
                Up(Down(J)) = J 
                Down(Up(J)) = J 

                Count(Col(J)) += 1 

                J = Right(J) 
            Loop 
            I = Up(I) 
        Loop 

    End Sub 
End Class