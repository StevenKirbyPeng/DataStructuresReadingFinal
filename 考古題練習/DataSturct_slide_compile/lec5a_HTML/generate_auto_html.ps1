# Generate two different HTML files from output SVG folders.
# index.html = one-step player with speed/autoplay.
# auto_generated_index.html = all images gallery, no step player.
# C++ source files are not modified.
$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$outputDir = Join-Path $root "output"
if (!(Test-Path $outputDir)) { Write-Host "output folder not found"; exit 1 }

$css = @'
body{font-family:"Microsoft JhengHei",Arial,sans-serif;margin:0;background:#f4f7fb;color:#1f2937;line-height:1.75}header{background:#1f4e79;color:white;padding:28px 36px}header h1{margin:0;font-size:28px}header p{margin:8px 0 0;color:#e5eef7}main{max-width:1180px;margin:24px auto;padding:0 18px}.note{background:white;border-left:6px solid #1f4e79;border-radius:12px;padding:16px 20px;margin-bottom:18px;box-shadow:0 3px 12px rgba(0,0,0,.08)}.topic{background:white;border-radius:14px;margin:18px 0;box-shadow:0 3px 14px rgba(0,0,0,.10);overflow:hidden}summary{cursor:pointer;font-weight:800;font-size:20px;padding:18px 22px;background:#eef5fb;display:flex;justify-content:space-between;align-items:center}summary span{font-size:14px;background:#1f4e79;color:white;border-radius:999px;padding:4px 10px}.panel{padding:20px}.explain{padding:18px 20px;background:#fffdf5;border:1px solid #f3dfb8;border-left:6px solid #d97706;border-radius:12px;margin-bottom:16px}.explain h3{margin:0 0 8px;color:#92400e}.explain p{margin:0;text-align:justify}.topbtn{border:0;border-radius:9px;background:#1f4e79;color:white;padding:8px 14px;font-weight:700;cursor:pointer}.controls{display:flex;gap:10px;align-items:center;flex-wrap:wrap;margin-bottom:14px}.controls button,.steps button{border:0;border-radius:9px;background:#1f4e79;color:white;padding:8px 14px;font-weight:700;cursor:pointer}.speed{padding:7px;border-radius:8px;border:1px solid #cbd5e1}.counter{font-weight:800;color:#1f4e79;background:#eaf2fb;border-radius:999px;padding:5px 12px}.viewer{border:1px solid #dbe3ef;border-radius:14px;background:#fff;min-height:420px;display:flex;align-items:center;justify-content:center;padding:14px}.mainFrame{max-width:100%;height:auto;max-height:720px}.steps{display:flex;gap:6px;flex-wrap:wrap;margin-top:12px}.steps button{background:#e6eef9;color:#1f4e79;padding:6px 10px}.steps button.activeStep{background:#1f4e79;color:white}.gallery{display:grid;grid-template-columns:repeat(auto-fit,minmax(280px,1fr));gap:14px}.frameCard{border:1px solid #dbe3ef;border-radius:12px;background:white;padding:10px}.frameCard h4{margin:0 0 8px;color:#1f4e79}.frameCard img{width:100%;height:auto;border:1px solid #e5e7eb;border-radius:8px}footer{text-align:center;color:#6b7280;padding:24px}
'@
$playerJs = @'
<script>
const timers={};function getFrames(id){return document.querySelector('#'+id+' .mainFrame').dataset.frames.split('|');}function updateButtons(box,idx){box.querySelectorAll('.steps button').forEach((b,i)=>b.classList.toggle('activeStep',i===idx));}function showFrame(id,idx){const box=document.getElementById(id);const img=box.querySelector('.mainFrame');const frames=getFrames(id);idx=(idx+frames.length)%frames.length;img.src=frames[idx];box.dataset.current=idx;box.querySelector('.counter').textContent='Step '+(idx+1)+' / '+frames.length;updateButtons(box,idx);}function nextFrame(id){const box=document.getElementById(id);showFrame(id,parseInt(box.dataset.current||'0')+1);}function prevFrame(id){const box=document.getElementById(id);showFrame(id,parseInt(box.dataset.current||'0')-1);}function togglePlay(id,btn){if(timers[id]){clearInterval(timers[id]);timers[id]=null;btn.textContent='Autoplay';return;}const box=document.getElementById(id);const speed=parseInt(box.querySelector('.speed').value||'1000');timers[id]=setInterval(()=>nextFrame(id),speed);btn.textContent='Pause';}document.addEventListener('change',e=>{if(e.target.classList.contains('speed')){const box=e.target.closest('.anim');const id=box.id;if(timers[id]){const btn=box.querySelector('.controls button:nth-child(2)');clearInterval(timers[id]);timers[id]=null;togglePlay(id,btn);}}});function openAll(){document.querySelectorAll('details.topic').forEach(d=>d.open=true)}function closeAll(){document.querySelectorAll('details.topic').forEach(d=>d.open=false)}document.addEventListener('DOMContentLoaded',()=>{document.querySelectorAll('.anim').forEach(a=>showFrame(a.id,0));});
</script>
'@
$galleryJs = '<script>function openAll(){document.querySelectorAll("details.topic").forEach(d=>d.open=true)}function closeAll(){document.querySelectorAll("details.topic").forEach(d=>d.open=false)}</script>'
function HtmlEncode([string]$s){ return [System.Net.WebUtility]::HtmlEncode($s) }
function Rel([string]$path){ return (($path.Substring($root.Length+1)) -replace '\\','/') }
$dirs = Get-ChildItem -Path $outputDir -Directory | Where-Object { $_.Name -like '*_steps' } | Sort-Object Name

$index = New-Object System.Text.StringBuilder
[void]$index.AppendLine('<!DOCTYPE html><html lang="zh-Hant"><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1.0"><title>lec5_a Step Player</title><style>'+$css+'</style></head><body><header><h1>lec5_a Step Player</h1><p>index.html: one-step player with speed and autoplay.</p><p><button class="topbtn" onclick="openAll()">Open all</button> <button class="topbtn" onclick="closeAll()">Close all</button></p></header><main><div class="note"><strong>Mode:</strong> Shows one current step image. Use previous, next, speed, and autoplay.</div>')
$i=0
foreach($dir in $dirs){
  $svgs = Get-ChildItem -Path $dir.FullName -Filter 'step_*.svg' | Sort-Object Name
  if($svgs.Count -eq 0){ continue }
  $title = (($dir.Name -replace '_steps$','') -replace '_',' ')
  $frames = ($svgs | ForEach-Object { Rel $_.FullName }) -join '|'
  [void]$index.AppendLine("<details class='topic' open><summary>$(HtmlEncode $title) <span>$($svgs.Count) steps</span></summary><div class='panel'><div class='explain'><h3>Animation explanation</h3><p>This topic uses sequential SVG frames to show how the data structure or algorithm changes step by step.</p></div><div class='anim' id='anim_$i' data-current='0' data-total='$($svgs.Count)'><div class='controls'><button type='button' onclick='prevFrame(""anim_$i"")'>Previous</button><button type='button' onclick='togglePlay(""anim_$i"", this)'>Autoplay</button><button type='button' onclick='nextFrame(""anim_$i"")'>Next</button><label>Time <select class='speed'><option value='500'>0.5s</option><option value='1000' selected>1s</option><option value='1500'>1.5s</option><option value='2000'>2s</option><option value='3000'>3s</option></select></label><span class='counter'>Step 1 / $($svgs.Count)</span></div><div class='viewer'><img class='mainFrame' src='$(Rel $svgs[0].FullName)' data-frames='$frames' alt='$(HtmlEncode $title)'></div><div class='steps'>")
  for($j=0;$j -lt $svgs.Count;$j++){ [void]$index.AppendLine("<button type='button' onclick='showFrame(""anim_$i"", $j)'>$($j+1)</button>") }
  [void]$index.AppendLine('</div></div></div></details>')
  $i++
}
[void]$index.AppendLine('</main><footer>Generated automatically.</footer>'+$playerJs+'</body></html>')
[System.IO.File]::WriteAllText((Join-Path $root 'index.html'), $index.ToString(), [System.Text.Encoding]::UTF8)

$auto = New-Object System.Text.StringBuilder
[void]$auto.AppendLine('<!DOCTYPE html><html lang="zh-Hant"><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1.0"><title>lec5_a All SVG Frames Gallery</title><style>'+$css+'</style></head><body><header><h1>lec5_a All SVG Frames Gallery</h1><p>auto_generated_index.html: all images shown directly, no step player.</p><p><button class="topbtn" onclick="openAll()">Open all</button> <button class="topbtn" onclick="closeAll()">Close all</button></p></header><main><div class="note"><strong>Mode:</strong> Shows every SVG frame as a gallery. No autoplay and no step-by-step control.</div>')
foreach($dir in $dirs){
  $svgs = Get-ChildItem -Path $dir.FullName -Filter 'step_*.svg' | Sort-Object Name
  if($svgs.Count -eq 0){ continue }
  $title = (($dir.Name -replace '_steps$','') -replace '_',' ')
  [void]$auto.AppendLine("<details class='topic' open><summary>$(HtmlEncode $title) <span>$($svgs.Count) images</span></summary><div class='panel'><div class='explain'><h3>Animation explanation</h3><p>This gallery lists all generated SVG frames for direct checking.</p></div><div class='gallery'>")
  $j=1
  foreach($svg in $svgs){ [void]$auto.AppendLine("<div class='frameCard'><h4>Step $j</h4><img src='$(Rel $svg.FullName)' alt='$(HtmlEncode $title) step $j'></div>"); $j++ }
  [void]$auto.AppendLine('</div></div></details>')
}
[void]$auto.AppendLine('</main><footer>Generated automatically.</footer>'+$galleryJs+'</body></html>')
[System.IO.File]::WriteAllText((Join-Path $root 'auto_generated_index.html'), $auto.ToString(), [System.Text.Encoding]::UTF8)
Write-Host 'Generated distinct index.html and auto_generated_index.html.'
