$ErrorActionPreference='Stop'
[Console]::OutputEncoding=[System.Text.Encoding]::UTF8
$OutputEncoding=[System.Text.Encoding]::UTF8
function RelPath($p){ return $p.Replace((Get-Location).Path + [IO.Path]::DirectorySeparatorChar,'').Replace('\\','/') }
$topicTitles=@{
'01_sequential_vs_linked'='Sequential vs. Linked Representation';
'02_singly_linked_chain'='Singly Linked Chain';
'03_node_class_and_has_a'='Node Class and Has-a Relation';
'04_pointer_manipulation'='Pointer Manipulation';
'05_create_insert_delete_chain'='Create Insert Delete Chain';
'06_template_chain_iterator'='Template Chain Iterator';
'07_insertback_concatenate_reverse'='InsertBack Concatenate Reverse';
'08_circular_list_last_pointer'='Circular List Last Pointer';
'09_circular_header_node'='Circular List with Header Node';
'10_linked_stack_queue'='Linked Stack and Queue';
'11_available_space_list'='Available Space List';
'12_polynomial_chain'='Polynomial Chain';
'13_polynomial_addition'='Polynomial Addition';
'14_sparse_matrix_orthogonal_list'='Sparse Matrix Orthogonal List';
'15_sparse_matrix_input_destructor'='Sparse Matrix Input and Destructor';
'16_doubly_linked_list'='Doubly Linked List';
}
$focus=@{
'01_sequential_vs_linked'=@{topic='比較連續記憶體與鏈結記憶體；示範插入造成搬移或改 pointer；理解 O(n) 與 O(1) 差異。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'02_singly_linked_chain'=@{topic='建立 first 指標；逐節點沿 link 前進；最後遇到 NULL 停止。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'03_node_class_and_has_a'=@{topic='節點分成 data 與 link；Chain 物件 has-a first pointer；說明封裝與節點關係。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'04_pointer_manipulation'=@{topic='先保存 next；把新節點指向後方；再讓前節點指向新節點。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'05_create_insert_delete_chain'=@{topic='從空串列建立；插入新節點；刪除時先接線再釋放。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'06_template_chain_iterator'=@{topic='泛型 T 存放資料；iterator 指向目前節點；++ 代表沿 link 移動。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'07_insertback_concatenate_reverse'=@{topic='尾端插入維持 last；串接兩條 chain；反轉每個 link 方向。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'08_circular_list_last_pointer'=@{topic='last 指向尾節點；last->link 回到第一個節點；用 last 可快速找到頭尾。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'09_circular_header_node'=@{topic='header 當固定入口；空表 header 指回自己；插入刪除不必處理特殊頭節點。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'10_linked_stack_queue'=@{topic='Stack 在 top push/pop；Queue 在 rear 插入、front 刪除；比較 LIFO 與 FIFO。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'11_available_space_list'=@{topic='刪除節點進入 av list；new node 可從 av list 取回；降低反覆配置成本。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'12_polynomial_chain'=@{topic='每節點存 coef 與 exp；依 exponent 排列；表示稀疏多項式。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'13_polynomial_addition'=@{topic='比較兩多項式指標；相同 exponent 相加；不同 exponent 複製較大項。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'14_sparse_matrix_orthogonal_list'=@{topic='非零元素用節點表示；row link 串同列；col link 串同欄。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'15_sparse_matrix_input_destructor'=@{topic='讀入 row col value；建立 row/col header；destructor 逐列釋放節點。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
'16_doubly_linked_list'=@{topic='每節點有 left/right link；可雙向走訪；插入刪除需更新四條 link。本主題屬於 Linked Lists 章節，重點在理解資料不一定連續放在記憶體中，而是透過 link/pointer 將節點串起來。考試常要求畫出操作前後的指標變化、判斷時間複雜度，以及說明 first、last、header、front、rear、iterator 等角色。';anim='動畫每一張 SVG 都由對應 C++ 程式輸出，不是手工貼圖。紅色區域代表此步驟正在新增、更新或強調的節點與指標；藍色或灰色區域代表已存在或背景結構。使用上一張/下一張可逐格檢查指標變化，使用自動播放可觀察整個資料結構如何從初始狀態逐步轉換成完成狀態。'};
}
function New-Page($path,[bool]$interactive){
$html='<!doctype html><html lang="zh-Hant"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>lec4 Linked Lists SVG Animation</title><style>body{font-family:Arial,''Microsoft JhengHei'',sans-serif;background:#f5f7fb;margin:0;color:#111}.wrap{max-width:1180px;margin:24px auto;padding:0 16px}h1{background:#123b63;color:white;padding:18px 22px;border-radius:14px}.card{background:white;border:1px solid #d7e0ea;border-radius:14px;margin:16px 0;box-shadow:0 2px 10px #0001}summary{font-size:22px;font-weight:700;padding:18px;cursor:pointer}.inner{padding:0 20px 22px}.desc{background:#eef6ff;border-left:6px solid #2b73bd;padding:14px 18px;border-radius:10px;margin:12px 0;line-height:1.8}.animdesc{background:#fff7d6;border-left:6px solid #d9a300;padding:14px 18px;border-radius:10px;margin:12px 0;line-height:1.8}.viewer{border:1px solid #d0dae6;border-radius:12px;background:#fff;padding:12px;margin-top:12px}.frame{width:100%;max-height:720px;object-fit:contain;border:1px solid #dde5ef;border-radius:10px;background:white}.controls{display:flex;gap:10px;align-items:center;flex-wrap:wrap;margin:12px 0}.btn{border:0;background:#1f6feb;color:white;padding:8px 14px;border-radius:8px;cursor:pointer}.btn.secondary{background:#475569}.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(230px,1fr));gap:12px}.thumb{border:1px solid #d0dae6;border-radius:10px;background:white;padding:8px}.thumb img{width:100%;height:160px;object-fit:contain}</style></head><body><div class="wrap"><h1>lec4 Linked Lists - C++ 產生 SVG 動畫、PowerShell 產生 HTML</h1>'
foreach($key in ($topicTitles.Keys|Sort-Object)){
 $steps=@(Get-ChildItem -Path (Join-Path 'output' ($key+'_steps')) -Filter 'step_*.svg'|Sort-Object Name|ForEach-Object{RelPath $_.FullName})
 if($steps.Count -eq 0){continue}
 $title=$topicTitles[$key]; $topic=$focus[$key].topic; $anim=$focus[$key].anim
 $html+="<details class='card'><summary>$title</summary><div class='inner'><div class='desc'><b>非常詳細主題說明：</b><br>$topic</div><div class='animdesc'><b>非常詳細動畫說明：</b><br>$anim</div>"
 if($interactive){$json=($steps|ConvertTo-Json -Compress).Replace('&','&amp;').Replace('<','&lt;').Replace('>','&gt;');$html+="<div class='viewer' data-steps='$json'><img class='frame' src='$($steps[0])'><div class='controls'><button class='btn prev'>上一張</button><button class='btn next'>下一張</button><button class='btn auto'>自動播放</button><button class='btn secondary stop'>停止</button><label>速度 <select class='speed'><option value='1500'>1.5 秒</option><option value='1000' selected>1 秒</option><option value='700'>0.7 秒</option><option value='400'>0.4 秒</option></select></label><span class='counter'>1 / $($steps.Count)</span></div></div>"} else {$html+='<div class="grid">'; foreach($s in $steps){$html+="<div class='thumb'><img src='$s'><div>$s</div></div>"}; $html+='</div>'}
 $html+='</div></details>'
}
$html+="</div><script>document.querySelectorAll('.viewer').forEach(v=>{const steps=JSON.parse(v.dataset.steps);let i=0,t=null;const img=v.querySelector('.frame'),c=v.querySelector('.counter');function show(){img.src=steps[i];c.textContent=(i+1)+' / '+steps.length;}v.querySelector('.prev').onclick=()=>{i=(i-1+steps.length)%steps.length;show();};v.querySelector('.next').onclick=()=>{i=(i+1)%steps.length;show();};v.querySelector('.auto').onclick=()=>{clearInterval(t);t=setInterval(()=>{i=(i+1)%steps.length;show();},parseInt(v.querySelector('.speed').value));};v.querySelector('.stop').onclick=()=>clearInterval(t);});</script></body></html>"
[IO.File]::WriteAllText($path,$html,[Text.UTF8Encoding]::new($true))
}
New-Page 'index.html' $true
New-Page 'auto_generated_index.html' $false
Write-Host 'Generated index.html and auto_generated_index.html'
