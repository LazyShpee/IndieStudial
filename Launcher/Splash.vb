Public Class Splash
    Dim strPath As String = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().CodeBase).Substring(6)

    Private Sub Splash_Load(sender As Object, e As EventArgs) Handles Me.Load
        Me.TransparencyKey = Color.Black
        Me.BackColor = Color.Black
        Me.TopMost = True
        Timer1.Interval = 10

        If My.Computer.FileSystem.FileExists(strPath + "\SuckMyWheels\done") Then
            MessageBox.Show("qlsdqlsdjk")
        End If

    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        If My.Computer.FileSystem.FileExists(strPath + "\SuckMyWheels\done") Then
            My.Computer.FileSystem.DeleteFile((strPath + "\SuckMyWheels\done"))
            Me.Close()
            MessageBox.Show("Lole")
        End If
    End Sub
End Class