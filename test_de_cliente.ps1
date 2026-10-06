$client = New-Object System.Net.Sockets.TcpClient("localhost", 9000)
$stream = $client.GetStream()
$reader = New-Object System.IO.StreamReader($stream)

Write-Host "Conectado al publicador en localhost:9000. Leyendo datos..."

while ($stream.CanRead) {
    $line = $reader.ReadLine()
    if ($line -eq $null) { break }
    Write-Host "Recibido por TCP: $line"
}