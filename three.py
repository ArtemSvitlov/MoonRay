import os
import json
import subprocess

# Словарь для отслеживания уникальных скелетов
skeleton_cache = {}

def get_fbx_bones_via_blender(file_path):
    """Использует Blender для извлечения имен костей из FBX."""
    blender_script = f"""
import bpy
import json
import os

try:
    bpy.ops.wm.read_factory_settings(use_empty=True)
    bpy.ops.import_scene.fbx(filepath='{file_path}')
    bones = []
    for obj in bpy.data.objects:
        if obj.type == 'ARMATURE':
            bones.extend([bone.name for bone in obj.data.bones])
    print("SKEL_START" + json.dumps(sorted(bones)) + "SKEL_END")
except:
    print("SKEL_START[]SKEL_END")
"""
    try:
        cmd = ["blender", "--background", "--python-expr", blender_script]
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=20)
        output = result.stdout
        if "SKEL_START" in output:
            start = output.find("SKEL_START") + len("SKEL_START")
            end = output.find("SKEL_END")
            return json.loads(output[start:end])
        return []
    except Exception:
        return []

def build_hierarchy(root_path, output_name):
    code_exts = {'.html', '.js', '.cpp', '.go', '.cs', '.py', '.ts', '.h', '.hpp'}
    ignore_list = {os.path.basename(__file__), output_name, 'venv', '.git', '__pycache__', 'node_modules'}
    
    # Список папок, содержимое которых мы не сканируем, если они в корне
    trusted_folders = {'lib', 'include'}

    def walk(path, is_root=False):
        name = os.path.basename(path) or path
        node = {"name": name, "type": "directory"}
        
        # ПРОВЕРКА: Если это папка lib или include на верхнем уровне
        if not is_root and name.lower() in trusted_folders:
            node["status"] = "можете быть уверены тут все норм"
            node["children"] = [] # Оставляем пустым, не идем вглубь
            return node

        node["children"] = []
        
        try:
            items = sorted(os.listdir(path))
            for item in items:
                if item in ignore_list:
                    continue
                
                full_path = os.path.join(path, item)
                if os.path.isdir(full_path):
                    # Передаем False для вложенных папок
                    node["children"].append(walk(full_path, is_root=False))
                else:
                    ext = os.path.splitext(item)[1].lower()
                    file_info = {"name": item, "type": "file", "ext": ext}
                    
                    if ext in code_exts:
                        try:
                            with open(full_path, 'r', encoding='utf-8', errors='replace') as f:
                                file_info["content"] = f.read()
                        except:
                            file_info["content"] = "Error reading file"
                    
                    elif ext == '.fbx':
                        bones = get_fbx_bones_via_blender(os.path.abspath(full_path))
                        if not bones:
                            file_info["skeleton"] = "No bones or error"
                        else:
                            skeleton_key = "|".join(bones)
                            if skeleton_key in skeleton_cache:
                                file_info["skeleton"] = f"the same as for {skeleton_cache[skeleton_key]}"
                            else:
                                skeleton_cache[skeleton_key] = item
                                file_info["skeleton"] = bones
                    
                    node["children"].append(file_info)
        except Exception as e:
            node["error"] = str(e)
            
        return node

    # Запускаем walk с флагом is_root=True для начальной папки
    result = walk(root_path, is_root=True)
    
    with open(output_name, 'w', encoding='utf-8') as f:
        json.dump(result, f, ensure_ascii=False, indent=4)

if __name__ == "__main__":
    OUT_FILE = "project_map.json"
    print("🔍 Начинаю сканирование проекта...")
    build_hierarchy(".", OUT_FILE)
    print(f"🚀 Готово! Результат записан в {OUT_FILE}")