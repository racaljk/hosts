
Start-Process "$psHome\powershell.exe"   -ArgumentList "if (Test-Path C:\Windows\System32\drivers\etc\hosts){Copy-Item C:\Windows\System32\drivers\etc\hosts C:\Windows\System32\drivers\etc\hosts.bak}; Invoke-RestMethod -uri https://raw.githubusercontent.com/racaljk/hosts/master/hosts -method get > C:\Windows\System32\drivers\etc\hosts"   -verb runas
