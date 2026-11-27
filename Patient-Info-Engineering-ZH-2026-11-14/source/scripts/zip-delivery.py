"""Package offline deliverables with portable UTF-8 filenames."""
from pathlib import Path
import sys
from zipfile import ZipFile, ZIP_DEFLATED

archive = Path(sys.argv[1])
root = Path(sys.argv[2])
with ZipFile(archive, 'x', ZIP_DEFLATED) as output:
    for relative in sys.argv[3:]:
        item = root / relative
        files = sorted(item.rglob('*')) if item.is_dir() else [item]
        for file in files:
            if file.is_file():
                output.write(file, file.relative_to(root).as_posix())
with ZipFile(archive) as result:
    assert result.testzip() is None
