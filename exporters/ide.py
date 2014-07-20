from uvision4 import Uvision4

IDE_SUPPORTED = {
    'uvision': Uvision4,
}

def export(data, ide):
    if ide is None:
        raise RuntimeError("No IDE selected in records.")
    if ide not in IDE_SUPPORTED:
        raise RuntimeError("Non supported IDE")

    Exporter = IDE_SUPPORTED[ide]
    exporter = Exporter()
    #run exporter for defined bootloader project
    exporter.generate(data)
