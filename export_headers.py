import os
import shutil
import argparse

def export_header_files(src_dir, dest_dir, extensions=('.h',), exclude_dirs=None):
    """
    导出头文件到指定目录，保留原始目录结构
    :param src_dir: 项目根目录
    :param dest_dir: 输出目录
    :param extensions: 头文件扩展名列表
    :param exclude_dirs: 要排除的目录列表
    """
    if exclude_dirs is None:
        exclude_dirs = []
    
    # 确保目标目录存在
    os.makedirs(dest_dir, exist_ok=True)
    print(f"导出位置: {dest_dir}")
    
    copied_count = 0
    skipped_count = 0
    
    for root, dirs, files in os.walk(src_dir):
        # 排除指定目录
        dirs[:] = [d for d in dirs if d not in exclude_dirs]
        
        for file in files:
            if file.lower().endswith(extensions):
                src_path = os.path.join(root, file)
                
                # 计算相对路径
                rel_path = os.path.relpath(root, src_dir)
                dest_path = os.path.join(dest_dir, rel_path, file)
                
                # 确保目标目录存在
                os.makedirs(os.path.dirname(dest_path), exist_ok=True)
                
                # 复制文件
                shutil.copy2(src_path, dest_path)
                print(f"已导出: {src_path} -> {dest_path}")
                copied_count += 1
    
    print(f"\n操作完成! 共导出 {copied_count} 个头文件")
    print(f"目标位置: {dest_dir}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='导出项目头文件工具')
    parser.add_argument('-s', '--source', default='.', 
                        help='源目录路径 (默认: 当前目录)')
    parser.add_argument('-d', '--dest', default='Include', 
                        help='目标目录路径 (默认: ./Include)')
    parser.add_argument('-e', '--exclude', nargs='*', default=['.git', 'build', 'bin'],
                        help='要排除的目录 (默认: .git build bin)')
    
    args = parser.parse_args()
    
    print("="*50)
    print(f"开始导出头文件")
    print(f"源目录: {os.path.abspath(args.source)}")
    print(f"目标目录: {os.path.abspath(args.dest)}")
    print(f"排除目录: {', '.join(args.exclude)}")
    print("="*50)
    
    export_header_files(
        src_dir=args.source,
        dest_dir=args.dest,
        extensions=('.h',),
        exclude_dirs=args.exclude
    )